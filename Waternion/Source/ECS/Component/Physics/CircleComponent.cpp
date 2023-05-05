#include"CircleComponent.h"

namespace Waternion::ECS
{
    CircleComponent::CircleComponent() : Component(), mCircle() {

    }

    void CircleComponent::OnStart() {
        mOwnerTransform = GetOwner()->GetComponent<TransformComponent>();
        mOwnerSprite = GetOwner()->GetComponent<SpriteComponent>();
        this->OnUpdateWorldTransform();
    }

    void CircleComponent::OnUpdate(float deltaTime) {
        WATERNION_LOG_INFO("Center (x: %f, y: %f)", mCircle.Center.x, mCircle.Center.y);
    }

    void CircleComponent::OnUpdateWorldTransform() {
        mCircle.Center.x = mOwnerTransform->GetPosition().x;
        mCircle.Center.y = mOwnerTransform->GetPosition().y;
        mCircle.Center.x += mOwnerSprite->GetScaledWidth() / 2.0f;
        mCircle.Center.y += mOwnerSprite->GetScaledHeight() / 2.0f;
    }
} // namespace Waternion::ECS