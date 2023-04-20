#pragma once

#include"Collisions/Primitive.h"
#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion::ECS
{
    class CircleComponent : public Component {
        public:
            CircleComponent();
            virtual void OnStart() override;
            virtual void OnUpdate(float deltaTime) override;
            WATERNION_INLINE const Circle& GetCircle() const {
                return mCircle;
            }
            WATERNION_INLINE void SetCenter(const Math::Vector2& center) {
                SetCenter(center.x, center.y);
            }
            WATERNION_INLINE void SetCenter(float x, float y) {
                mCircle.Center.x = x;
                mCircle.Center.y = y;
            }
            WATERNION_INLINE const Math::Vector2& GetCenter() const {
                return mCircle.Center;
            }
            WATERNION_INLINE void SetRadius(float radius) {
                mCircle.Radius = radius;
            }
            virtual void OnUpdateWorldTransform() override;
        private:
            Shared<TransformComponent> mOwnerTransform;
            Shared<SpriteComponent> mOwnerSprite;
            Circle mCircle;
    };
} // namespace Waternion::ECS