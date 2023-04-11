#include"SpriteComponent.h"
#include"Core/Manager/ResourceManager.h"
#include"Math/Matrix.h"
#include"Core/Application.h"

namespace Waternion::ECS {
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

        mBox.UpdateMinMax(Math::Vector2(0.0f, 0.0f));
        mBox.UpdateMinMax(Math::Vector2(1.0f, 1.0f));
    }

    void SpriteComponent::Draw(Shared<Shader> shader, float deltaTime) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        
        mSize.x = mTexture->Width * transform->GetScale().x;
        mSize.y = mTexture->Height * transform->GetScale().y;
        Math::Matrix4 model = Math::Matrix4::CreateFromScale(mSize.x, mSize.y, 1.0f);
        model *= Math::Matrix4::CreateFromTranslation(-mSize.x / 2, -mSize.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromRotationZ(transform->GetRotation());
        model *= Math::Matrix4::CreateFromTranslation(mSize.x / 2, mSize.y / 2, 0.0f);
        model *= Math::Matrix4::CreateFromTranslation(transform->GetPosition());

        shader->Use();
        shader->SetMatrix4("Transform", model);
        shader->SetVector3("color", mColor);
        shader->SetInt("image", 0);
        mVAO->Bind();
        mTexture->Bind();
        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    float SpriteComponent::GetWidth() const {
        return mTexture->Width * GetOwner()->GetComponent<TransformComponent>()->GetScale().x;
    }

    float SpriteComponent::GetHeight() const {
        return mTexture->Height * GetOwner()->GetComponent<TransformComponent>()->GetScale().y;
    }

    void SpriteComponent::CheckError() {
        GLenum error = glGetError();
        switch (error)
        {
        case GL_NO_ERROR:
            WATERNION_LOG_INFO("Render sprite with NO ERROR!");
            break;
        case GL_INVALID_ENUM:
            WATERNION_LOG_ERROR("Render sprite with INVALID ENUM!");
            break;
        case GL_INVALID_VALUE:
            WATERNION_LOG_ERROR("Render sprite with INVALID VALUE!");
            break;
        case GL_INVALID_OPERATION:
            WATERNION_LOG_ERROR("Render sprite with INVALID OPERATION!");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            WATERNION_LOG_ERROR("Render sprite with FRAMEBUFFER OPERATION!");
            break;
        case GL_OUT_OF_MEMORY:
            WATERNION_LOG_ERROR("Render sprite with OUT OF MEMORY!");
            break;
        default:
            WATERNION_LOG_ERROR("Render sprite with UNDETECED ERROR");
            break;
        }
    }
}