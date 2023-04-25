#include"Particle2DComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"Core/Application.h"
#include"Core/Manager/ResourceManager.h"
#include"Utils/Settings.h"

namespace Waternion::ECS
{
    Particle2DComponent::Particle2DComponent() : 
        SpriteComponent(), mParticlesPerFrame(3), mMaxParticles(500), mLastUsedIdx(0) 
    {
        mParticles.resize(mMaxParticles);
        mModels.resize(mMaxParticles);
        mColors.resize(mMaxParticles);
    }

    void Particle2DComponent::Init(const char* filepath, bool alpha, const char* name) {
        SpriteComponent::Init(filepath, alpha, name);
        // Add transform instanced VBO
        glGenBuffers(1, &mTransformInstancedVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mTransformInstancedVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Math::Matrix4) * mMaxParticles, mModels.data(), GL_DYNAMIC_DRAW);
        GetVertexArray()->Bind();
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Math::Matrix4), nullptr);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Math::Matrix4), ReintepretCast<void*>(sizeof(float) * 4));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Math::Matrix4), ReintepretCast<void*>(sizeof(float) * 8));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Math::Matrix4), ReintepretCast<void*>(sizeof(float) * 12));
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        // Add color instanced VBO
        glGenBuffers(1, &mColorInstancedVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mColorInstancedVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Math::Vector4) * mMaxParticles, mColors.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Math::Vector4), nullptr);
        glVertexAttribDivisor(6, 1);
        GetVertexArray()->Unbind();
    }
    
    void Particle2DComponent::OnStart() {
        mOwnerTransform = GetOwner()->GetComponent<TransformComponent>();
        mOwnerSprite = GetOwner()->GetComponent<SpriteComponent>();
        float spriteWidth = mOwnerSprite->GetWidth();
        float spriteHeight = mOwnerSprite->GetHeight();
        const Math::Matrix4& orthoProj = Math::Matrix4::CreateOrtho(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight(), -10.0f, 1000.0f);
        // Set particle defeault shader
        Shared<Shader> shader = ResourceManager::LoadShader(Settings::ParticleVertexSource, Settings::ParticleFragmentSource, "", Settings::ParticleShaderName);
        shader->Use();
        shader->SetMatrix4("Projection", orthoProj);
        shader->SetVector2("offset", -spriteWidth / 16.0f);
        shader->SetInt("image", 0);
        SpriteComponent::SetShader(shader);
    }

    void Particle2DComponent::OnUpdate(float deltaTime) {
        this->RespawnParticles(-mOwnerSprite->GetWidth() / 2.0f);
        this->UpdateParticles(deltaTime);
    }

    void Particle2DComponent::Draw(float deltaTime) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        GetShader()->Use();
        GetVertexArray()->Bind();
        GetTexture()->Bind();
        glActiveTexture(GL_TEXTURE0);

        float spriteWidth = mOwnerSprite->GetWidth();
        float spriteHeight = mOwnerSprite->GetHeight();
        for (uint32_t i = 0 ; i < mMaxParticles; i++) {
            const Particle& particle = mParticles[i];

            if (particle.LifeTime < 0.0f) {
                continue;
            }

            Math::Matrix4 model = Math::Matrix4::CreateFromScale(spriteWidth, spriteHeight, 1.0f);
            model *= Math::Matrix4::CreateFromTranslation(-spriteWidth / 2, -spriteHeight / 2, 0.0f);
            model *= Math::Matrix4::CreateFromScale(mOwnerTransform->GetScale() * 1.1f);
            model *= Math::Matrix4::CreateFromRotationZ(mOwnerTransform->GetRotation());
            model *= Math::Matrix4::CreateFromTranslation(spriteWidth / 2, spriteHeight / 2, 0.0f);
            model *= Math::Matrix4::CreateFromTranslation(particle.Position);
            mModels[i] = model;
            mColors[i] = particle.Color;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, mTransformInstancedVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Math::Matrix4) * mMaxParticles, mModels.data());

        glBindBuffer(GL_ARRAY_BUFFER, mColorInstancedVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Math::Vector4) * mMaxParticles, mColors.data());

        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, mMaxParticles);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Particle2DComponent::UpdateParticles(float deltaTime) {
        for (uint32_t i = 0; i < mMaxParticles; i++) {
            Particle& particle = mParticles[i];
            particle.LifeTime -= deltaTime;
            if (particle.LifeTime > 0.0f) {
                particle.Position -= particle.Velocity * deltaTime;
                particle.Color.w -= deltaTime * 2.0f;
            }
        }
    }

    void Particle2DComponent::RespawnParticles(const Math::Vector2& offset) {
        for (uint32_t i = 0; i < mParticlesPerFrame; i++) {
            this->SpawnParticles(mParticles[this->GetUnusedParticleIdx()], offset);
        }
    }

    void Particle2DComponent::SpawnParticles(Particle& particle, const Math::Vector2& offset) {
        float random = ((rand() % 100) - 50) / 10.0f;
        float color = 0.5f + ((rand() % 100) / 100.0f);
        particle.Position.x = mOwnerTransform->GetPosition().x + random + offset.x;
        particle.Position.y = mOwnerTransform->GetPosition().y + random + offset.y;
        particle.Color = color;
        particle.Color.w = 1.0f;
        particle.LifeTime = mLifeTime;
        particle.Velocity = GetOwner()->GetComponent<MoveComponent>()->GetVelocity() * 0.08f;
        particle.Velocity.y = 30.0f;
    }

    uint32_t Particle2DComponent::GetUnusedParticleIdx() {
        for (uint32_t i = mLastUsedIdx; i < mMaxParticles; i++) {
            if (mParticles[i].LifeTime <= 0.0f) {
                mLastUsedIdx = i;
                return i;
            }
        }
        for (uint32_t i = 0; i < mLastUsedIdx; i++) {
            if (mParticles[i].LifeTime <= 0.0f) {
                mLastUsedIdx = i;
                return i;
            }
        }
        mLastUsedIdx = 0;
        return 0;
    }
} // namespace Waternion::ECS