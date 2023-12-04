#pragma once

#include"Application.h"

extern Waternion::Application* Waternion::CreateApplication();

int main() {
    Waternion::Application* application = Waternion::CreateApplication();

    bool success = application->Init(1920, 1080, "Waternion");
    
    if (success) {
        application->Run();
    }

    application->Shutdown();
    WATERNION_FREE(application);

    return 1;
}