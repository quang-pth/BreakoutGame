#include"Renderer.h"

#include"ECS/Component/Graphics/AnimatorComponent.h"

namespace Waternion
{
    namespace ECS {
        void AnimationSystem::Update(float deltaTime) {
            for (const auto&  entity : GetEntitiesHaveComponent<AnimatorComponent>()) {
                entity->GetComponent<AnimatorComponent>()->OnUpdate(deltaTime);
            }
        }

        void AnimationSystem::Draw(float deltaTime) {
            for (const auto&  entity : GetEntitiesHaveComponent<AnimatorComponent>()) {
                entity->GetComponent<AnimatorComponent>()->Draw(deltaTime);
            }
        }
    }
} // namespace Waternion