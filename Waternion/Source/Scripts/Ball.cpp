#include"Ball.h"
#include"ECS/System/InputSystem.h"
#include"Core/Application.h"
#include"ECS/Component/Physics/CircleComponent.h"

namespace Waternion
{
    using namespace ECS;

    Ball::Ball() : NativeScript(), mIsMoving(false), mIsStick(true), mForwardSpeed(200.0f) {

    }

    Ball::Ball(EntityID id) : NativeScript(id), mIsMoving(false), mIsStick(true), mForwardSpeed(200.0f) {

    }

    void Ball::OnAwake() {
        mPaddle = Application::GetInstance()->GetScene()->GetEntity("Paddle");
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.045f);
        mTransform->SetPositionZ(1.0f);
        
        mSprite = AddComponent<SpriteComponent>();
        mSprite->Init("assets/textures/awesomeface.png", true, "Ball");
        
        mMove = AddComponent<MoveComponent>();

        Shared<CircleComponent> circle = AddComponent<CircleComponent>();
        circle->SetRadius(mSprite->GetWidth() / 2.0f);
    }

    void Ball::OnStart() {
        mTransform->SetPositionY(mPaddle->GetComponent<TransformComponent>()->GetPosition().y + mSprite->GetHeight() / 2.0f);
    }

    void Ball::OnProcessInput(const InputState& inputState) {
        if (mIsMoving) return;

        if (inputState.Keyboard.GetKeyState(GLFW_KEY_SPACE) == ButtonState::EPressed) {
            mIsMoving = true;
            mIsStick = false;
            mMove->SetForwardSpeed(mForwardSpeed);
        }
    }

    void Ball::OnUpdate(float deltaTime) {
        if (mIsMoving) return;

        const Math::Vector3& paddlePosition = mPaddle->GetComponent<TransformComponent>()->GetPosition();
        Shared<SpriteComponent> paddleSprite = mPaddle->GetComponent<SpriteComponent>();
        mTransform->SetPositionX(paddlePosition.x + paddleSprite->GetWidth() / 2.0f - mSprite->GetHeight() / 2.0f);
    }

    void Ball::OnPostUpdate(float deltaTime) {
        if (mIsMoving) {
            mMove->Update(deltaTime);
        }
    }

    void Ball::OnCollision(Shared<ECS::Entity> collidedEntity) {
        mMove->SetForwardSpeed(0.0f);
    }
} // namespace Waternion