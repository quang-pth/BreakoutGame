#include"Layer.h"
#include"Layer/Layer.h"
#include"Core/Application.h"

namespace Waternion
{
    Layer::Layer() {
        Application::GetInstance()->PushLayer(this);
    }
} // namespace Waternion