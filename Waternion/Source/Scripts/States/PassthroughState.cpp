#include"PassthroughState.h"

#include"Scripts/Ball.h"
#include"Scripts/PlayerController.h"
#include"Scripts/States/StickState.h"

// Components
#include"ECS/Component/Graphics/Particle2DComponent.h"

namespace Waternion
{
    PassthroughState::PassthroughState() : MovingState() {

    }

    PassthroughState::PassthroughState(Ball* owner) : MovingState(owner) {

    }

    void PassthroughState::OnEnter() {
        mOwner->mSprite->SetColor(Math::Vector4(1.0f, 0.5f, 0.5f));
    }

    void PassthroughState::OnExit() {
        mOwner->mSprite->SetColor(Math::Vector4(1.0f));
    }

    void PassthroughState::OnUpdate(float deltaTime) {
        MovingState::OnUpdate(deltaTime);
    }

    void PassthroughState::OnCollision(const ECS::CollisionDetails& details) {
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
        if (!collider->GetComponent<ECS::InfoComponent>()->GetTag().compare("Solid")) {
            mOwner->ResolveCollidesWithBricks(mSpeed, details);
            return;
        }
    }
} // namespace Waternion