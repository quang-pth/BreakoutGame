#pragma once

#include"ECS/Component/Defaults.h"
#include"Collisions/Primitive.h"

namespace Waternion::ECS
{
    class Box2DComponent : public Component {
        public:
            Box2DComponent();
            virtual void OnStart() override;
            virtual void OnUpdateWorldTransform() override;
            void SetBox(const AABB2D& box) {
                mLocalBox = box;
            }
            WATERNION_INLINE const AABB2D& GetBox() const {
                return mWorldBox;
            }
        private:
            AABB2D mLocalBox;
            AABB2D mWorldBox;
    };
} // namespace Waternion::ECS