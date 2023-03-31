#include<Core/Application.h>

int main() {
    Waternion::Application application;
    bool success = application.InitWindow(800, 600, "BreakOut", "v0.1");
    if (success) {
        application.Run();
    }

    application.Shutdown();
    return 1;
}