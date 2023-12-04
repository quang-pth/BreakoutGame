#include"SpriteComponent.h"
#include"Core/Manager/ResourceManager.h"
#include"Math/Matrix.h"
#include"Core/Application.h"

#include"Utils/Settings.h"

namespace Waternion::ECS {
    SpriteComponent::SpriteComponent() : 
        Component(), mColor(Math::Vector4(1.0f)), mIsVisible(true), mBox()  
    {

    }
    
    SpriteComponent::SpriteComponent(const char* filepath, bool alpha, const char* name) : 
        Component(), mColor(Math::Vector4(1.0f)), mIsVisible(true), mBox()  
    {
        this->Init(filepath, alpha, name);
    }

    void SpriteComponent::Init(const char* filepath, bool alpha, const char* name) {
        mTexture = ResourceManager::LoadTexture(filepath, alpha, name);
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        mSize.x = mTexture->Width * transform->GetScale().x;
        mSize.y = mTexture->Height * transform->GetScale().y;
        
        float vertices[] = {
            // Position       // Texcoords
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f
        };
        int32_t numOfVertices = sizeof(vertices) / sizeof(float);
        
        int32_t indices[] = {
            0, 1, 2, // first triangle
            3, 4, 5 // second  triangle
        };
        int32_t numOfIndices = sizeof(indices) / sizeof(int32_t);

        mVAO = MakeShared<VertexArray>(vertices, numOfVertices, indices, numOfIndices);
        mShader = ResourceManager::LoadShader(Settings::DefaultVertexSource, Settings::DefaultFragmentSource, "", Settings::DefaultShaderName);
        const Math::Matrix4& orthoProj = Math::Matrix4::CreateOrtho(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight(), -10.0f, 1000.0f);
        mShader->Use();
        mShader->SetMatrix4("Projection", orthoProj);

        mBox.UpdateMinMax(Math::Vector2(0.0f, 0.0f));
        mBox.UpdateMinMax(Math::Vector2(1.0f, 1.0f));
    }

    void SpriteComponent::Draw(float deltaTime) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();

        mSize.x = mTexture->Width * transform->GetScale().x;
        mSize.y = mTexture->Height * transform->GetScale().y;
        Math::Matrix4 model = Math::Matrix4::CreateFromScale(mSize.x, mSize.y, 1.0f);
        model *= Math::Matrix4::CreateFromTranslation(-mSize.x / 2, -mSize.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromRotationZ(transform->GetRotation());
        model *= Math::Matrix4::CreateFromTranslation(mSize.x / 2, mSize.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromTranslation(transform->GetPosition());

        mShader->Use();
        mShader->SetMatrix4("Transform", model);
        mShader->SetVector4("color", mColor);
        mShader->SetInt("image", 0);
        mVAO->Bind();
        mTexture->Bind();
        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    float SpriteComponent::GetScaledWidth() const {
        return mTexture->Width * GetOwner()->GetComponent<TransformComponent>()->GetScale().x;
    }

    float SpriteComponent::GetScaledHeight() const {
        return mTexture->Height * GetOwner()->GetComponent<TransformComponent>()->GetScale().y;
    }

    float SpriteComponent::GetTextureWidth() const {
        return mTexture->Width;
    }

    float SpriteComponent::GetTextureHeight() const {
        return mTexture->Height;
    }

    void SpriteComponent::SetShader(Shared<Shader> shader) {
        mShader = shader;
    }

    void SpriteComponent::SetShader(const char* shaderName) {
        mShader = ResourceManager::GetShader(shaderName);
    }
}