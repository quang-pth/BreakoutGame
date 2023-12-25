#include"Leviathan.h"

// Components
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"ECS/Component/Graphics/AnimatorComponent.h"

#include"Core/Application.h"
#include"Core/Event/Event.h"

#include"Render/SpriteSheet.h"

namespace Waternion {
    using namespace ECS; 

    void Leviathan::OnAwake() {
        SpriteSheet* spriteSheet = new SpriteSheet("assets/MegamanZero/leviathan-swim-forward.png", 54, 64);
        Shared<Animation> animation = MakeShared<Animation>("Swim", spriteSheet->GetSprites(), true);        
        animation->AnimationFPS = 10;

        Shared<AnimatorComponent> animator = AddComponent<AnimatorComponent>();
        animator->AddAnimation(animation);
    }

    void Leviathan::OnStart() {
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(0.0f, 0.0f, 100.0f);
    }

    void Leviathan::OnWindowResized(const WindowResizedEvent& event) {
        Shared<TransformComponent> transform = GetComponent<TransformComponent>();
        transform->SetPosition(-event.GetWidth() / 2.0f, -event.GetHeight() / 2.0f, 100.0f);
    }
}