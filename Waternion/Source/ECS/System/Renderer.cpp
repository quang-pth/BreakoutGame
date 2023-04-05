#include"Renderer.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"

namespace Waternion::ECS
{
    bool SpriteRenderer::Init() {
        System::Init();
        return true;
    }

    void SpriteRenderer::Draw(Shared<Shader> shader) {
        for (Shared<Entity> entity : System::GetEntitiesHasComponentType<SpriteComponent>()) {
            entity->GetComponent<SpriteComponent>()->Draw(shader);
        }
    }
} // namespace Waternion