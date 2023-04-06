#include"Renderer.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"
#include"ECS/Component/SpriteComponent.h"

namespace Waternion::ECS
{
    bool SpriteRenderer::Init() {
        System::Init();
        return true;
    }

    void SpriteRenderer::Draw(Shared<Shader> shader, float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<SpriteComponent>()) {
            entity->GetComponent<SpriteComponent>()->Draw(shader, deltaTime);
        }
    }
} // namespace Waternion