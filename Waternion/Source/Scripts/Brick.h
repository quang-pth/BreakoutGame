#pragma once

#include"Native.h"
#include"Math/Vec.h"

namespace Waternion
{
    class Brick : public NativeScript {
        public:
            Brick();
            Brick(ECS::EntityID id);
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
            bool mIsSolid;
            bool mIsDestroyed;
    }; 
} // namespace Waternion
