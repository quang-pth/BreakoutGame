#pragma once

#include"Native.h"
#include"Math/Vec.h"

namespace Waternion
{
    namespace ECS {
        class SoundComponent;
    };

    class Brick : public NativeScript {
        public:
            Brick();
            Brick(ECS::EntityID id);
            virtual void OnCollision(const ECS::CollisionDetails& details) override;
            virtual void OnActivate() override;
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
            WATERNION_INLINE void SetRow(uint32_t row) {
                mRow = row;
            }
            WATERNION_INLINE void SetCol(uint32_t col) {
                mCol = col;
            }
            void Place(float width, float height, float unitWidth, float unitHeight);
        private:
            void SpawnPowerUpWithProbability(float probability = 0.3f);
            bool mIsSolid;
            bool mIsDestroyed;
            Shared<class PowerManager> mPowerManager;
            Shared<class GameLevel> mGameLevel;
            uint32_t mRow, mCol;
            float mUnitWidth, mUnitHeight;
    }; 
} // namespace Waternion
