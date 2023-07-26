#include"SandboxApplication.h"
#include"Client/Scene/MainScene.h"

namespace Client
{
    SandboxApplication::SandboxApplication() : Waternion::Application() {

    }

    bool SandboxApplication::Init(int width, int height, const std::string& title) {
        Application::AddScene(new MainScene());
        return Waternion::Application::Init(width, height, title);
    }
} // namespace Client