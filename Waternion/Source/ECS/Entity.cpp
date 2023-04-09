#include"Entity.h"
#include"Core/Application.h"
#include"Component/Defaults.h"

namespace Waternion {
    namespace ECS {
        Entity::Entity(const std::string& name) {
            mCoordinator = Application::GetInstance()->GetCoordinator();
            WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");
            mID = mCoordinator->AddEntity();
            this->AddComponent<InfoComponent>()->SetName(name);
            this->AddComponent<TransformComponent>();

            Application::GetInstance()->GetScene()->AddEntity(mID);
        }

        Entity::Entity(EntityID id, Shared<Coordinator> coordinator) : mID(id), mCoordinator(coordinator) {

        }
    }
}