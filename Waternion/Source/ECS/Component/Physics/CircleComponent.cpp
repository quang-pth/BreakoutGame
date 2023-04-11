#include"CircleComponent.h"

namespace Waternion::ECS
{
    CircleComponent::CircleComponent() : Component(), mCircle(), mDisabled(false) {

    }

    void CircleComponent::OnStart() {
        mOwnerTransform = GetOwner()->GetComponent<TransformComponent>();
        mOwnerSprite = GetOwner()->GetComponent<SpriteComponent>();
        this->OnUpdateWorldTransform();
    }

    void CircleComponent::OnUpdate(float deltaTime) {
    }

    void CircleComponent::OnUpdateWorldTransform() {
        // mCircle.Center.x = mOwnerTransform->GetPosition().x;
        // mCircle.Center.y = mOwnerTransform->GetPosition().y;
        // mCircle.Center.x += mOwnerSprite->GetScaledWidth() / 2.0f;
        // mCircle.Center.y += mOwnerSprite->GetScaledHeight() / 2.0f;
    }
} // namespace Waternion::ECS