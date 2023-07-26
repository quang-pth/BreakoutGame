#include<Core/Entry.h>
#include"Client/SandboxApplication.h"

Waternion::Application* Waternion::CreateApplication() {
    return new Client::SandboxApplication();
}