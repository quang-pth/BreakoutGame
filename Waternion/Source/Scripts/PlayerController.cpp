#include"PlayerController.h"
#include"ECS/System/InputSystem.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/SpriteComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"Core/Application.h"

namespace Waternion
{
    using namespace ECS;

    void PlayerController::OnAwake() {
        float windowWidth = Application::GetInstance()->GetWindowWidth();
        float windowHeight = Application::GetInstance()->GetWindowHeight();
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.16f, 0.1f, 1.0f);
        mTransform->SetPosition(-windowWidth / 8.0f, -windowHeight / 2.0f, 10.0f);

        mMoveComponent = AddComponent<MoveComponent>();
        Shared<SpriteComponent> sprite = AddComponent<SpriteComponent>();
        sprite->Init("assets/textures/paddle.png", true, "Paddle");;

        Shared<Box2DComponent> box = AddComponent<Box2DComponent>();
        box->SetBox(sprite->GetBox());
    }
    
    void PlayerController::OnProcessInput(const InputState& inputState) {
        float strafeSpeed = 0.0f;
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_A)) {
            strafeSpeed -= mMaxSpeed;
        }
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_D)) {
            strafeSpeed += mMaxSpeed;
        }

        mMoveComponent->SetStrafeSpeed(strafeSpeed);
    }

    void PlayerController::OnPreUpdate(float deltaTime) {
    }

    void PlayerController::OnUpdate(float deltaTime) {
        mMoveComponent->Update(deltaTime);
    }

    void PlayerController::OnPostUpdate(float deltaTime) {

    }
} // namespace Waternion