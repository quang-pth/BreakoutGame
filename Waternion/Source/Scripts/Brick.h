#pragma once

#include"Native.h"
#include"Math/Vec.h"

namespace Waternion
{
    class Brick : public NativeScript {
        public:
            Brick();
            Brick(ECS::EntityID id);
            virtual void OnStart() override;
            virtual void OnCollision(const ECS::CollisionDetails& details) override;
            WATERNION_INLINE void SetIsSolid(bool solid) {
                mIsSolid = solid;
            }
            WATERNION_INLINE bool GetIsSolid() const {
                return mIsSolid;
            }
            WATERNION_INLINE void SetIsDestroyed(bool destroyed) {
                mIsDestroyed = destroyed;
            }
            WATERNION_INLINE bool GetIsDestroyed() const {
                return mIsDestroyed;
            }
        private:
            void SpawnPowerUpWithProbability(float probability = 0.3f);
            bool mIsSolid;
            bool mIsDestroyed;
            Shared<class PowerManager> mPowerManager;
    }; 
} // namespace Waternion
