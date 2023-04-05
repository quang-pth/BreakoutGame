#include"SpriteComponent.h"
#include"Core/Manager/ResourceManager.h"
#include"Math/Matrix.h"
#include"Core/Application.h"

namespace Waternion::ECS {
    void SpriteComponent::Init(const char* filepath, bool alpha, const char* name) {
        mTexture = ResourceManager::LoadTexture(filepath, alpha, name);
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
        mOwner = Component::GetEntity<SpriteComponent>();
    }

    void SpriteComponent::Draw(Shared<Shader> shader) {
        Shared<TransformComponent> transform = mOwner->GetComponent<TransformComponent>();
        const Math::Matrix4& scaleMatrix = Math::Matrix4::CreateFromScale(mTexture->Width, mTexture->Height, 1.0f);
        
        shader->Use();
        shader->SetMatrix4("Transform", const_cast<Math::Matrix4&>(scaleMatrix) * const_cast<Math::Matrix4&>(transform->GetWorldTransform()));
        mVAO->Bind();
        mTexture->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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