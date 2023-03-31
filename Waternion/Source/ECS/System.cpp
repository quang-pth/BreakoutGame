#include"System.h"
#include"Core/Application.h"

namespace Waternion
{
    namespace ECS {
        System::System() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
        }
    }
} // namespace Waternion