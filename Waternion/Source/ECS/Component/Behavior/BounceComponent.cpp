#include"BounceComponent.h"

namespace Waternion::ECS
{
    BounceComponent::BounceComponent() : MoveComponent(), mDirection(Math::Vector3::Zero) {

    }

    void BounceComponent::Bounce() {
        
    }
} // namespace Waternion::ECS