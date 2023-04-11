#include"Box2DComponent.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/SpriteComponent.h"

namespace Waternion::ECS
{
    Box2DComponent::Box2DComponent() : Component(), mLocalBox(), mWorldBox(), mDisabled(false) {

    }

    void Box2DComponent::OnUpdateWorldTransform() {
        mWorldBox = mLocalBox;

        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        Shared<SpriteComponent> sprite = GetOwner()->GetComponent<SpriteComponent>();
        // Scale
        mWorldBox.Min.x *= transform->GetScale().x;
        mWorldBox.Min.y *= transform->GetScale().y;
        mWorldBox.Max.x *= transform->GetScale().x;
        mWorldBox.Max.y *= transform->GetScale().y;
        // Translate
        mWorldBox.Min.x += transform->GetPosition().x;
        mWorldBox.Min.y += transform->GetPosition().y;
        mWorldBox.Max.x += mWorldBox.Min.x + sprite->GetWidth();
        mWorldBox.Max.y += mWorldBox.Min.y + sprite->GetHeight();
    }
}