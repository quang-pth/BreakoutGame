#include"System.h"
#include"Core/Application.h"
#include"ECS/Component/Defaults.h"

namespace Waternion
{
    namespace ECS {
        System::System() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
        }

        void System::PreUpdate(float deltaTime) {
            for (Shared<Entity> entity : GetEntitiesHaveComponent<TransformComponent>()) {
                entity->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
        }

        void System::Update(float deltaTime) {

        }

        void System::PostUpdate(float deltaTime) {
            for (Shared<Entity> entity : GetEntitiesHaveComponent<TransformComponent>()) {
                entity->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
        }
    }
} // namespace Waternion