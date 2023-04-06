#include"PlayerController.h"
#include"ECS/System/InputSystem.h"
#include"ECS/Component/Defaults.h"

namespace Waternion
{
    using namespace ECS;

    void PlayerController::OnStart() {
        mMoveComponent = GetComponent<MoveComponent>();
    }

    void PlayerController::OnProcessInput(const InputState& inputState) {

        float strafeSpeed = 0.0f;
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_A)) {
            strafeSpeed -= mMaxSpeed;
        }
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_D)) {
            strafeSpeed += mMaxSpeed;
        }

        float verticalSpeed = 0.0f;
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_W)) {
            verticalSpeed += mMaxSpeed;
        }
        if (inputState.Keyboard.GetKeyValue(GLFW_KEY_S)) {
            verticalSpeed -= mMaxSpeed;
        }

        mMoveComponent->SetSpeed(strafeSpeed, verticalSpeed, 0.0f);
    }

    void PlayerController::OnUpdate(float deltaTime) {
        mMoveComponent->Update(deltaTime);
    }

    void PlayerController::OnPostUpdate(float deltaTime) {
        mMoveComponent->SetSpeed(0.0f, 0.0f, 0.0f);
    }
} // namespace Waternion