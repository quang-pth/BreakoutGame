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
        }

        void System::Update(float deltaTime) {

        }

        void System::PostUpdate(float deltaTime) {
        }
    }
} // namespace Waternion