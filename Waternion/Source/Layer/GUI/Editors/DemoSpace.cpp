#include"DemoSpace.h"

namespace Waternion::Editor
{
    DemoSpace::DemoSpace() : Editor() {

    }

    void DemoSpace::OnRender() {
        ImGui::ShowDemoWindow();
    }
} // namespace Waternion::Editor
