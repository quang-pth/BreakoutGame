#pragma once

#include"ECS/Component/Defaults.h"
#include"Collisions/Primitive.h"

namespace Waternion::ECS
{
    class Box2DComponent : public Component {
        public:
            Box2DComponent();
            virtual void OnUpdateWorldTransform() override;
            void SetBox(const AABB2D& box) {
                mLocalBox = box;
            }
            WATERNION_INLINE const AABB2D& GetBox() const {
                return mWorldBox;
            }
            WATERNION_INLINE void SetDisabled(bool disabled) {
                mDisabled = disabled;
            }
            WATERNION_INLINE bool GetDisabled() const {
                return mDisabled;
            }
        private:
            AABB2D mLocalBox;
            AABB2D mWorldBox;
            bool mDisabled;
    };
} // namespace Waternion::ECS