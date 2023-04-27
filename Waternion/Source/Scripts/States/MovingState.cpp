#include"MovingState.h"
#include"Scripts/Ball.h"
#include"StickState.h"

// Components
#include"ECS/Component/Behavior/MoveComponent.h"
#include"ECS/Component/Audio/SoundComponent.h"
#include"ECS/Component/Physics/Box2DComponent.h"
#include"ECS/Component/Physics/CircleComponent.h"
#include"ECS/Component/UI/TextComponent.h"

#include"Scripts/GameManager.h"

#include"Core/Application.h"

namespace Waternion
{
    const static float MAX_INTERVAL = 0.5f;

    MovingState::MovingState() {

    }

    MovingState::MovingState(Ball* owner) : BallState(owner), mDisabledDuration(0.0f), mSpeed(300.0f) {
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
            mOwner->SetLives(mOwner->mLives - 1);
            if (mOwner->mLives == 0) {
                mOwner->mGameManager->SetGameState(EGameState::Lose);
            }
            mOwner->ChangeState<StickState>();
        }
    }

    void MovingState::OnCollision(const ECS::CollisionDetails& details) {
        Shared<ECS::Entity> collider = details.Collider;
        // The ball collides with player's paddle
        if (collider->GetID() == mOwner->mPaddle->GetID()) {
            if (!mOwner->mPaddle->GetComponent<ECS::InfoComponent>()->GetTag().compare("Stickable")) {
                mOwner->ChangeState<StickState>();
            }
            else {
                mOwner->ResolveCollidesWithPaddle(mSpeed);
            }
            return;
        }
        // The ball collides with powerups
        if (!collider->GetComponent<ECS::InfoComponent>()->GetTag().compare("Ignore")) {
            return;
        }
        // The ball collides with other bricks
        mOwner->ResolveCollidesWithBricks(mSpeed, details);
    }
} // namespace Waternion