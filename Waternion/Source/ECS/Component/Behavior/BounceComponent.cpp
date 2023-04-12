#include"BounceComponent.h"

namespace Waternion::ECS
{
    BounceComponent::BounceComponent() : MoveComponent(), mDirection(Math::Vector3::Zero) {

    }

    void BounceComponent::BounceVertical() {
        SetForwardSpeed(GetForwardSpeed() * -1.0f);
    }

    void BounceComponent::BounceHorizontal() {
        SetStrafeSpeed(GetStrafeSpeed() * -1.0f);
    }
} // namespace Waternion::ECS