#pragma once

#include"ECS/Component/Defaults.h"

namespace Waternion::ECS {
    class MoveComponent : public Component {
        public:
            MoveComponent();
            virtual void Update(float deltaTime);
            WATERNION_INLINE void SetStrafeSpeed(float speed) {
                mStrafeSpeed = speed;
            }
            WATERNION_INLINE float GetStrafeSpeed() const {
                return mStrafeSpeed;
            }
            WATERNION_INLINE void SetForwardSpeed(float speed) {
                mForwardSpeed = speed;
            }
            WATERNION_INLINE float GetForwardSpeed() const {
                return mForwardSpeed;
            }
        protected:
            bool IsInBoundsX(const Math::Vector3& position);
            bool IsInBoundsY(const Math::Vector3& position);
            virtual void BounceVertical();
            virtual void BounceHorizontal();
        private:
            float mStrafeSpeed;
            float mForwardSpeed;
    };
}