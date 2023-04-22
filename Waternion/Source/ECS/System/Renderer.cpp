#include"Renderer.h"
#include"Core/Manager/ResourceManager.h"
#include"Core/Application.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Graphics/Particle2DComponent.h"

namespace Waternion::ECS
{
    bool SpriteRenderer::Init() {
        WATERNION_LOG_INFO("SpriteRenderer is intialized successfully!");
        return true;
    }

    void SpriteRenderer::Shutdown() {
        mSpritesMap.clear();
        WATERNION_LOG_INFO("SpriteRenderer is closed!");
    }

    void SpriteRenderer::BeginScene(float deltaTime) {
        std::vector<Shared<SpriteComponent>> sprites;
        // Get renderable components
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<SpriteComponent>()) {
            Shared<SpriteComponent> sprite = entity->GetComponent<SpriteComponent>();
            if (!sprite->GetDisabled() || sprite->GetIsVisible()) {
                sprites.emplace_back(sprite);
            }
        }
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<Particle2DComponent>()) {
            Shared<Particle2DComponent> particle = entity->GetComponent<Particle2DComponent>();
            if (!particle->GetDisabled() || particle->GetIsVisible()) {
                sprites.emplace_back(particle);
            }
        }
        std::sort(sprites.begin(), sprites.end(), [](Shared<SpriteComponent> a, Shared<SpriteComponent> b) {
            Shared<TransformComponent> t1 = a->GetOwner()->GetComponent<TransformComponent>();
            Shared<TransformComponent> t2 = b->GetOwner()->GetComponent<TransformComponent>();
            return t1->GetPosition().z < t2->GetPosition().z;
        });
        // Groups sprites by shader
        for (Shared<SpriteComponent> sprite : sprites) {
            uint32_t shaderID = sprite->GetShader()->ID;
            mSpritesMap[shaderID].emplace_back(sprite);
        }
    }

    void SpriteRenderer::Draw(float deltaTime) {
        for (const auto&[_, sprites] : mSpritesMap) {
            for (auto iter = sprites.rbegin(); iter != sprites.rend(); iter++) {
                (*iter)->Draw(deltaTime);
            }
        }
    }

    void SpriteRenderer::EndScene(float deltaTime) {
        mSpritesMap.clear();
    }
} // namespace Waternion