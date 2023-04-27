#include"Background.h"

// Components
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"

#include"Core/Application.h"

namespace Waternion {
    using namespace ECS;

    void Background::OnAwake() {
        Shared<SpriteComponent> sprite = AddComponent<SpriteComponent>();
        sprite->Init("assets/textures/background.jpg", false, "Background");

        Shared<SoundComponent> sound = AddComponent<SoundComponent>("assets/audio/breakout.mp3", true);
        sound->Play();
    }

    void Background::OnUpdate(float deltaTime) {
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(-windowWidth / 2.0f, -windowHeight / 2.0f, 100.0f);
    }
}