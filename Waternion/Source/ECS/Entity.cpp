#include"Entity.h"
#include"Core/Application.h"
#include"Component/Defaults.h"

namespace Waternion {
    namespace ECS {
        Entity::Entity() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
            WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");
            mID = mCoordinator->AddEntity();
            this->AddComponent<InfoComponent>();
            this->AddComponent<TransformComponent>();
        }

        Entity::Entity(EntityID id, Shared<Coordinator> coordinator) : mID(id), mCoordinator(coordinator) {

        }
    }
}