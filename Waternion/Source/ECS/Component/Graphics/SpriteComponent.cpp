#include"SpriteComponent.h"
#include"Core/Manager/ResourceManager.h"
#include"Math/Matrix.h"
#include"Core/Application.h"

#include"Utils/Settings.h"

namespace Waternion::ECS {
    SpriteComponent::SpriteComponent() : 
        Component(), mIsVisible(true), mBox()  
    {
        mSprite = new Sprite();
        mSprite->Color = Math::Vector4(1.0f);
    }

    void SpriteComponent::Init(const char* filepath, bool alpha, const char* name) {
        mSprite->Texture = ResourceManager::LoadTexture(filepath, alpha, name);
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        mSprite->Size.x = mSprite->Texture->Width * transform->GetScale().x;
        mSprite->Size.y = mSprite->Texture->Height * transform->GetScale().y;
        
        Vertex vertices[] = {
            Vertex(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 1.0f)),
            Vertex(Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 0.0f)),
            Vertex(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector2(0.0f, 0.0f)),

            Vertex(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector2(0.0f, 1.0f)),
            Vertex(Math::Vector3(1.0f, 1.0f, 0.0f), Math::Vector2(1.0f, 1.0f)),
            Vertex(Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(1.0f, 0.0f)),
        };
        int32_t numOfVertices = sizeof(vertices) / sizeof(Vertex);
        
        int32_t indices[] = {
            0, 1, 2, // first triangle
            3, 4, 5 // second  triangle
        };
        int32_t numOfIndices = sizeof(indices) / sizeof(int32_t);

        mSprite->VAO = MakeShared<VertexArray>(vertices, numOfVertices, indices, numOfIndices);
        mSprite->Shader = ResourceManager::LoadShader(Settings::DefaultVertexSource, Settings::DefaultFragmentSource, "", Settings::DefaultShaderName);

        mBox.UpdateMinMax(Math::Vector2(0.0f, 0.0f));
        mBox.UpdateMinMax(Math::Vector2(1.0f, 1.0f));
    }

    void SpriteComponent::Draw(float deltaTime) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();

        mSprite->Size.x = mSprite->Texture->Width * transform->GetScale().x;
        mSprite->Size.y = mSprite->Texture->Height * transform->GetScale().y;
        Math::Matrix4 model = Math::Matrix4::CreateFromScale(mSprite->Size.x, mSprite->Size.y, 1.0f);
        model *= Math::Matrix4::CreateFromTranslation(-mSprite->Size.x / 2, -mSprite->Size.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromRotationZ(transform->GetRotation());
        model *= Math::Matrix4::CreateFromTranslation(mSprite->Size.x / 2, mSprite->Size.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromTranslation(transform->GetPosition());
        const Math::Matrix4& orthoProj = Math::Matrix4::CreateOrtho(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight(), -10.0f, 1000.0f);

        mSprite->Shader->Use();
        mSprite->Shader->SetMatrix4("Projection", orthoProj);
        mSprite->Shader->SetMatrix4("Transform", model);
        mSprite->Shader->SetVector4("color", mSprite->Color);
        mSprite->Shader->SetInt("image", 0);
        mSprite->VAO->Bind();
        mSprite->Texture->Bind();
        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    float SpriteComponent::GetScaledWidth() const {
        return mSprite->Texture->Width * GetOwner()->GetComponent<TransformComponent>()->GetScale().x;
    }

    float SpriteComponent::GetScaledHeight() const {
        return mSprite->Texture->Height * GetOwner()->GetComponent<TransformComponent>()->GetScale().y;
    }

    float SpriteComponent::GetTextureWidth() const {
        return mSprite->Texture->Width;
    }

    float SpriteComponent::GetTextureHeight() const {
        return mSprite->Texture->Height;
    }

    void SpriteComponent::SetShader(Shared<Shader> shader) {
        mSprite->Shader = shader;
    }

    void SpriteComponent::SetShader(const char* shaderName) {
        mSprite->Shader = ResourceManager::GetShader(shaderName);
    }
}