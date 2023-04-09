#pragma once

#include"MoveComponent.h"

namespace Waternion::ECS
{
    class BounceComponent : public MoveComponent {
        public:
            BounceComponent();
        protected:
            virtual void Bounce() override;
        private:
            Math::Vector3 mDirection;
    };
} // namespace Waternion::ECS