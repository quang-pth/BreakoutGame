#include"Ball.h"
#include"ECS/System/InputSystem.h"
#include"Core/Application.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"

namespace Waternion
{
    using namespace ECS;

    const static float MAX_INTERVAL = 0.5f;

    Ball::Ball() : 
        NativeScript(), mIsMoving(false), 
        mIsStick(true), mSpeed(200.0f), mDisabledDuration(0.0f)
    {

    }

    Ball::Ball(EntityID id) : NativeScript(id), mIsMoving(false), mIsStick(true), mSpeed(200.0f) {

    }

    void Ball::OnAwake() {
        mPaddle = Application::GetInstance()->GetScene()->GetEntity("Paddle");
        mTransform = GetComponent<TransformComponent>();
        mTransform->SetScale(0.045f);
        mTransform->SetPositionZ(1.0f);
        
        mSprite = AddComponent<SpriteComponent>();
        mSprite->Init("assets/textures/awesomeface.png", true, "Ball");
        
        mBounce = AddComponent<BounceComponent>();

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
            mDisabledDuration = MAX_INTERVAL;
            mPaddle->GetComponent<Box2DComponent>()->SetDisabled(true);
            mBounce->SetForwardSpeed(mSpeed);
        }
    }

    void Ball::OnUpdate(float deltaTime) {
        if (mIsMoving) {
            mDisabledDuration -= deltaTime;
            if (mDisabledDuration < 0.0f) {
                mPaddle->GetComponent<Box2DComponent>()->SetDisabled(false);
                mDisabledDuration = MAX_INTERVAL;
            }
            return;
        }

        const Math::Vector3& paddlePosition = mPaddle->GetComponent<TransformComponent>()->GetPosition();
        Shared<SpriteComponent> paddleSprite = mPaddle->GetComponent<SpriteComponent>();
        mTransform->SetPositionX(paddlePosition.x + paddleSprite->GetWidth() / 2.0f - mSprite->GetHeight() / 2.0f);
    }

    void Ball::OnPostUpdate(float deltaTime) {
        if (mIsMoving) {
            mBounce->Update(deltaTime);
        }
    }

    void Ball::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> collider = details.Collider;
        if (mIsMoving) {
            const Math::Vector2& bounceDirection = details.ClosestDirection;
            if (bounceDirection == Math::Vector2::UnitX) {
                mBounce->SetStrafeSpeed(mSpeed);
                mTransform->SetPositionX(mTransform->GetPosition().x + details.Penetration);
            }
            else if (bounceDirection == -Math::Vector2::UnitX) {
                mBounce->SetStrafeSpeed(-mSpeed);
                mTransform->SetPositionX(mTransform->GetPosition().x - details.Penetration);
            }
            else if (bounceDirection == Math::Vector2::UnitY) {
                mBounce->SetForwardSpeed(mSpeed);
                mTransform->SetPositionY(mTransform->GetPosition().y + details.Penetration);
            }
            else if (bounceDirection == -Math::Vector2::UnitY) {
                mBounce->SetForwardSpeed(-mSpeed);
                mTransform->SetPositionY(mTransform->GetPosition().y - details.Penetration);
            }
        }
    }
} // namespace Waternion