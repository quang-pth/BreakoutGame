#pragma once

#include"Application.h"

extern Waternion::Application* Waternion::CreateApplication();

int main() {
    Waternion::Application* application = Waternion::CreateApplication();

    bool success = application->Init();
    
    if (success) {
        application->Run();
    }

    application->Shutdown();
    delete application;
    application = nullptr;

    return 1;
}