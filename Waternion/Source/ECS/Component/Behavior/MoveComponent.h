#pragma once

#include"ECS/Component/Defaults.h"

namespace Waternion::ECS {
    class MoveComponent : public Component {
        public:
            MoveComponent();
            void Update(float deltaTime);
            WATERNION_INLINE const Math::Vector3& GetSpeed() const { return mSpeed; }
            WATERNION_INLINE void SetSpeed(const Math::Vector3& speed) { 
                mSpeed = speed; 
            }
            WATERNION_INLINE void SetSpeed(float x, float y, float z) { 
                mSpeed.x = x;
                mSpeed.y = y; 
                mSpeed.z = z;
            }
        private:
            Math::Vector3 mSpeed;
    };
}