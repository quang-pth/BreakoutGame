#include"Background.h"

// Components
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"

#include"Core/Application.h"
#include"Core/Event/Event.h"

namespace Waternion {
    using namespace ECS;

    void Background::OnAwake() {
        Shared<SpriteComponent> sprite = AddComponent<SpriteComponent>();
        sprite->Init("assets/textures/background.jpg", false, "Background");

        Shared<SoundComponent> sound = AddComponent<SoundComponent>("assets/audio/breakout.mp3", true);
        sound->Play();
    }

    void Background::OnStart() {
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(-windowWidth / 2.0f, -windowHeight / 2.0f, 100.0f);
    }

    void Background::OnWindowResized(const WindowResizedEvent& event) {
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(-event.GetWidth() / 2.0f, -event.GetHeight() / 2.0f, 100.0f);
    }
}