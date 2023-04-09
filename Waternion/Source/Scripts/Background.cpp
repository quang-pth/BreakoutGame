#include"Background.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/SpriteComponent.h"
#include"Core/Application.h"

namespace Waternion {
    using namespace ECS;

    void Background::OnStart() {
        Shared<SpriteComponent> sprite = AddComponent<SpriteComponent>();
        sprite->Init("assets/textures/background.jpg", false, "Background");

        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(-windowWidth / 2.0f, -windowHeight / 2.0f, -100.0f);
    }
}