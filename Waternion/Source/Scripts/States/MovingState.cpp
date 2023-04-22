#include"MovingState.h"
#include"Scripts/Ball.h"
#include"StickState.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"

#include"Core/Application.h"

namespace Waternion
{
    const static float MAX_INTERVAL = 0.5f;

    MovingState::MovingState() {

    }

    MovingState::MovingState(Ball* owner) : BallState(owner), mSpeed(300.0f), mDisabledDuration(0.0f) {
    }

    MovingState::~MovingState() {

    }

    void MovingState::OnEnter() {
        mDisabledDuration = MAX_INTERVAL;
        mOwner->mPaddle->GetComponent<ECS::Box2DComponent>()->SetDisabled(true);
        mOwner->mMove->SetForwardSpeed(mSpeed);
    }

    void MovingState::OnExit() {

    }

    void MovingState::OnUpdate(float deltaTime) {
        mDisabledDuration -= deltaTime;
        if (mDisabledDuration < 0.0f) {
            mOwner->mPaddle->GetComponent<ECS::Box2DComponent>()->SetDisabled(false);
            mDisabledDuration = MAX_INTERVAL;
        }

        bool inUpperBound, inLowerBound;
        mOwner->mMove->IsInBoundsY(inLowerBound, inUpperBound);
        if (!inLowerBound) {
            Shared<BallState> newState = BallState::ChangeState<StickState>();
            this->OnExit();
            newState->OnEnter();
            mOwner->mState = newState;
        }
    }

    void MovingState::OnCollision(const ECS::CollisionDetails& details) {
        Shared<ECS::Entity> collider = details.Collider;
        // The ball collides with player's paddle
        if (collider->GetID() == mOwner->mPaddle->GetID()) {
            Shared<ECS::TransformComponent> paddleTransform = mOwner->mPaddle->GetComponent<ECS::TransformComponent>(); 
            Shared<ECS::SpriteComponent> paddleSprite = mOwner->mPaddle->GetComponent<ECS::SpriteComponent>();
            float paddleCenterX = paddleTransform->GetPosition().x + paddleSprite->GetWidth() / 2.0f;
            float distanceToCenter = mOwner->GetComponent<ECS::CircleComponent>()->GetCenter().x - paddleCenterX;
            
            float percentage = distanceToCenter / (paddleSprite->GetWidth() / 2.0f);
            float strength = 4.5f;

            const Math::Vector2& oldVelocity = mOwner->mMove->GetVelocity();
            Math::Vector2 newVelocity(mSpeed * strength * percentage, Math::Abs(oldVelocity.y) * 1.0f);
            newVelocity.SafeNormalized();

            mOwner->mMove->SetStrafeSpeed(newVelocity.x * mSpeed);
            mOwner->mMove->SetForwardSpeed(Math::Clamp(newVelocity.y * mSpeed, 100.0f, 300.0f));
            return;
        }
        // The ball collides with powerups
        if (!collider->GetComponent<ECS::InfoComponent>()->GetTag().compare("Ignore")) {
            return;
        }
        // The ball collides with other bricks
        const Math::Vector2& bounceDirection = details.ClosestDirection;
        if (bounceDirection == Math::Vector2::UnitX) {
            mOwner->mMove->SetStrafeSpeed(mSpeed);
            mOwner->mTransform->SetPositionX(mOwner->mTransform->GetPosition().x + details.Penetration);
        }
        else if (bounceDirection == -Math::Vector2::UnitX) {
            mOwner->mMove->SetStrafeSpeed(-mSpeed);
            mOwner->mTransform->SetPositionX(mOwner->mTransform->GetPosition().x - details.Penetration);
        }
        else if (bounceDirection == Math::Vector2::UnitY) {
            mOwner->mMove->SetForwardSpeed(mSpeed);
            mOwner->mTransform->SetPositionY(mOwner->mTransform->GetPosition().y + details.Penetration);
        }
        else if (bounceDirection == -Math::Vector2::UnitY) {
            mOwner->mMove->SetForwardSpeed(-mSpeed);
            mOwner->mTransform->SetPositionY(mOwner->mTransform->GetPosition().y - details.Penetration);
        }
    }
} // namespace Waternion