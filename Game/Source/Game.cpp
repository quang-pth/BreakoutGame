#include<Core/Application.h>

int main() {
    bool success = Waternion::Application::GetInstance()->Init(800, 600, "BreakOut", "v0.1");
    
    if (success) {
        Waternion::Application::GetInstance()->Run();
    }

    Waternion::Application::GetInstance()->Shutdown();
    return 1;
}