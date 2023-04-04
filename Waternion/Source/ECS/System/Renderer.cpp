#include"Renderer.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"

namespace Waternion::ECS
{
    bool SpriteRenderer::Init() {
        System::Init();
        Application::GetInstance()->GetScene()->RegisterSystem<SpriteRenderer>();
        return true;
    }

    void SpriteRenderer::Draw(Shared<Shader> shader) {
        for (Shared<Entity>& entity : System::GetEntitiesHasComponentType<SpriteComponent>()) {
            Shared<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
            sprite->Draw(shader);
        }
    }
} // namespace Waternion