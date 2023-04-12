#pragma once

#include"Primitive.h"

namespace Waternion {
    struct CircleCollider {
        float Penetration;
        bool Intersected;
        Math::Vector2 ContactedPoint;
    };

    class Collisions {
        public:
            WATERNION_INLINE static CircleCollider IsIntersect(const Circle& circle, const AABB2D& box) {
                Math::Vector2 diffVector = circle.Center - box.GetCenterPoint();
                const Math::Vector2& boxSize = box.GetSize();
                diffVector = Math::Vector2::Clamp(diffVector, -boxSize * 0.5f, boxSize * 0.5f);
                const Math::Vector2& closestPoint = box.GetCenterPoint() + diffVector;
                const Math::Vector2& distanceVector = closestPoint - circle.Center;

                CircleCollider collider;
                collider.ContactedPoint = closestPoint;
                collider.Intersected = circle.Contains(closestPoint);
                collider.Penetration = Math::Abs(distanceVector.Magnitude() - circle.Radius);

                return collider;
            }
        private:
            Collisions() = default;
    };
}