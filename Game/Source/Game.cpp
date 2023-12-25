#include<Core/Application.h>

int main() {
    int success = Waternion::Application::GetInstance()->Init(800, 600, "MegamanZero", "project-zero");

    if (success) {
        Waternion::Application::GetInstance()->Run();
    }

    Waternion::Application::GetInstance()->Shutdown();
    return 0;
}