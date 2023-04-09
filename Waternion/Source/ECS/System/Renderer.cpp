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

    void SpriteRenderer::BeginScene(float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<SpriteComponent>()) {
            Shared<TransformComponent> transform = entity->GetComponent<TransformComponent>();
            Shared<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
            mSprites.emplace_back(sprite);
        }
        std::sort(mSprites.begin(), mSprites.end(), [](Shared<SpriteComponent> a, Shared<SpriteComponent> b) {
            Shared<TransformComponent> t1 = a->GetOwner()->GetComponent<TransformComponent>();
            Shared<TransformComponent> t2 = b->GetOwner()->GetComponent<TransformComponent>();
            return t1->GetPosition().z < t2->GetPosition().z;
        });
    }

    void SpriteRenderer::Draw(Shared<Shader> shader, float deltaTime) {
        for(Shared<SpriteComponent> sprite : mSprites) {
            sprite->Draw(shader, deltaTime);
        }
    }

    void SpriteRenderer::EndScene(float deltaTime) {
        mSprites.clear();
    }
} // namespace Waternion