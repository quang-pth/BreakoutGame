#include"MoveComponent.h"

namespace Waternion::ECS {
    MoveComponent::MoveComponent() : 
        Component(), mSpeed(Math::Vector3::Zero)
    {

    }

    void MoveComponent::Update(float deltaTime) {
        Shared<TransformComponent> transform = GetOwner()->GetComponent<TransformComponent>();
        const Math::Vector3& pos = transform->GetPosition();
        transform->SetPosition(pos + mSpeed * deltaTime);
    }
}