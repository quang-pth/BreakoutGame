#include"SpriteComponent.h"
#include"Core/Manager/ResourceManager.h"
#include"Math/Matrix.h"

namespace Waternion::ECS {
    SpriteComponent::SpriteComponent(const char* filepath, bool alpha, const char* name) {
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
        uint32_t indices[] = {
            0, 1, 2, // first triangle
            3, 4, 5
        };
        mVAO = MakeShared<VertexArray>(vertices, 6, indices, 6);
    }

    void SpriteComponent::Draw(Shared<Shader> shader) {
        shader->Use();
        static Math::Matrix4 transform = Math::Matrix4::Identity;
        shader->SetMatrix4("Transform", transform);
        shader->SetMatrix4("Projection", transform);
        mVAO->Bind();
        glActiveTexture(0);
        mTexture->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}