#include"StickState.h"
#include"MovingState.h"
#include"Scripts/Ball.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"

namespace Waternion
{
    StickState::StickState() {

    }

    StickState::StickState(Ball* owner) : BallState(owner) {

    }

    StickState::~StickState() {

    }

    void StickState::OnEnter() {
        mOwner->mMove->SetForwardSpeed(0.0f);
        mOwner->mMove->SetStrafeSpeed(0.0f);
        mOwner->mTransform->SetPositionY(mOwner->mPaddle->GetComponent<ECS::TransformComponent>()->GetPosition().y + mOwner->mSprite->GetHeight() / 2.0f);
    }

    void StickState::OnExit() {

    }

    void StickState::OnProcessInput(const InputState& inputState) {
        if (inputState.Keyboard.GetKeyState(GLFW_KEY_SPACE) == ButtonState::EPressed) {
            Shared<BallState> newState = BallState::ChangeState<MovingState>();
            this->OnExit();
            newState->OnEnter();
            mOwner->mState = newState;
        }
    }

    void StickState::OnUpdate(float deltaTime) {
        const Math::Vector3& paddlePosition = mOwner->mPaddle->GetComponent<ECS::TransformComponent>()->GetPosition();
        Shared<ECS::SpriteComponent> paddleSprite = mOwner->mPaddle->GetComponent<ECS::SpriteComponent>();
        mOwner->mTransform->SetPositionX(paddlePosition.x + paddleSprite->GetWidth() / 2.0f - mOwner->mSprite->GetHeight() / 2.0f);
    }
} // namespace Waternions