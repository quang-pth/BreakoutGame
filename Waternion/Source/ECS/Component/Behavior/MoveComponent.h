#pragma once

#include"ECS/Component/Defaults.h"

namespace Waternion::ECS {
    class WATERNION_API MoveComponent : public Component {
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
            Math::Vector2 GetVelocity() const;
            void IsInBoundsX(bool& inLeftBound, bool& inRightBound);
            void IsInBoundsY(bool& inLowerBound, bool& inUpperBound);
            void SetSpeedScale(float scale);
        private:
            float mStrafeSpeed;
            float mForwardSpeed;
    };
}