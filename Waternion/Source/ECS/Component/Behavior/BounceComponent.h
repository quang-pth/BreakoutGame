#pragma once

#include"MoveComponent.h"

namespace Waternion::ECS
{
    class BounceComponent : public MoveComponent {
        public:
            BounceComponent();
        protected:
            virtual void BounceVertical() override;
            virtual void BounceHorizontal() override;
        private:
            Math::Vector3 mDirection;
    };
} // namespace Waternion::ECS