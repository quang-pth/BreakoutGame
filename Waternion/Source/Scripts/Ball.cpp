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
        mIsStick(true), mSpeed(400.0f), mDisabledDuration(0.0f)
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
        
        mMove = AddComponent<MoveComponent>();

        Shared<CircleComponent> circle = AddComponent<CircleComponent>();
        circle->SetRadius(mSprite->GetWidth() / 2.0f);
    }

    void Ball::OnStart() {
        this->Reset();
    }

    void Ball::OnProcessInput(const InputState& inputState) {
        if (mIsMoving) return;

        if (inputState.Keyboard.GetKeyState(GLFW_KEY_SPACE) == ButtonState::EPressed) {
            mIsMoving = true;
            mIsStick = false;
            mDisabledDuration = MAX_INTERVAL;
            mPaddle->GetComponent<Box2DComponent>()->SetDisabled(true);
            mMove->SetForwardSpeed(mSpeed);
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
            mMove->Update(deltaTime);
            this->ConstraintsInBoundsX();
            this->ConstraintsInBoundsY();
        }
    }

    void Ball::OnCollision(const ECS::CollisionDetails& details) {
        Shared<Entity> collider = details.Collider;
        if (mIsMoving) {
            // The ball collides with player's paddle
            if (collider->GetID() == mPaddle->GetID()) {
                Shared<TransformComponent> paddleTransform = mPaddle->GetComponent<TransformComponent>(); 
                Shared<SpriteComponent> paddleSprite = mPaddle->GetComponent<SpriteComponent>();
                float paddleCenterX = paddleTransform->GetPosition().x + paddleSprite->GetWidth() / 2.0f;
                float distanceToCenter = GetComponent<CircleComponent>()->GetCenter().x - paddleCenterX;
               
                float percentage = distanceToCenter / (paddleSprite->GetWidth() / 2.0f);
                float strength = 3.0f;

                const Math::Vector2& oldVelocity = mMove->GetVelocity();
                Math::Vector2 newVelocity(mSpeed * strength * percentage, Math::Abs(oldVelocity.y) * 1.0f);
                newVelocity.SafeNormalized();

                mMove->SetStrafeSpeed(newVelocity.x * oldVelocity.Magnitude());
                mMove->SetForwardSpeed(newVelocity.y * oldVelocity.Magnitude());
                return;
            }
            // The ball collides with other bricks
            const Math::Vector2& bounceDirection = details.ClosestDirection;
            if (bounceDirection == Math::Vector2::UnitX) {
                mMove->SetStrafeSpeed(mSpeed);
                mTransform->SetPositionX(mTransform->GetPosition().x + details.Penetration);
            }
            else if (bounceDirection == -Math::Vector2::UnitX) {
                mMove->SetStrafeSpeed(-mSpeed);
                mTransform->SetPositionX(mTransform->GetPosition().x - details.Penetration);
            }
            else if (bounceDirection == Math::Vector2::UnitY) {
                mMove->SetForwardSpeed(mSpeed);
                mTransform->SetPositionY(mTransform->GetPosition().y + details.Penetration);
            }
            else if (bounceDirection == -Math::Vector2::UnitY) {
                mMove->SetForwardSpeed(-mSpeed);
                mTransform->SetPositionY(mTransform->GetPosition().y - details.Penetration);
            }
        }
    }

    void Ball::Reset() {
        mTransform->SetPositionY(mPaddle->GetComponent<TransformComponent>()->GetPosition().y + mSprite->GetHeight() / 2.0f);
        mIsMoving = false;
        mIsStick = true;
        mMove->SetStrafeSpeed(0.0f);
        mMove->SetForwardSpeed(0.0f);
    }

    void Ball::ConstraintsInBoundsX() {
        bool inLeftBound, inRightBound;
        mMove->IsInBoundsX(inLeftBound, inRightBound);
        
        if (!inLeftBound) {
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / -2.0f);
        }

        if (!inRightBound) {
            mTransform->SetPositionX(Application::GetInstance()->GetWindowWidth() / 2.0f - mSprite->GetWidth() / 2.0f);
        }

        if (!inLeftBound || !inRightBound) {
            mMove->SetStrafeSpeed(mMove->GetStrafeSpeed() * -1.0f);
        }

    }
    
    void Ball::ConstraintsInBoundsY() {
        bool inLowerBound, inUpperBound;
        mMove->IsInBoundsY(inLowerBound, inUpperBound);
        
        if (!inLowerBound) {
            this->Reset();
        }
        else if (!inUpperBound) {
            mTransform->SetPositionY(Application::GetInstance()->GetWindowHeight() / 2.0f - mSprite->GetHeight() / 2.0f);
            mMove->SetForwardSpeed(mMove->GetForwardSpeed() * -1.0f);
        }
    }
} // namespace Waternion