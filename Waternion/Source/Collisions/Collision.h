#pragma once

#include"Primitive.h"

namespace Waternion {
    struct ColliderInfo {
        float Penetration;
        bool Intersected;
        Math::Vector2 ContactedPoint;
    };

    class Collisions {
        public:
            WATERNION_INLINE static ColliderInfo IsIntersect(const Circle& circle, const AABB2D& box) {
                Math::Vector2 diffVector = circle.Center - box.GetCenterPoint();
                const Math::Vector2& boxSize = box.GetSize();
                diffVector = Math::Vector2::Clamp(diffVector, -boxSize * 0.5f, boxSize * 0.5f);
                const Math::Vector2& closestPoint = box.GetCenterPoint() + diffVector;
                const Math::Vector2& distanceVector = closestPoint - circle.Center;

                ColliderInfo collider;
                collider.ContactedPoint = closestPoint;
                collider.Intersected = circle.Contains(closestPoint);
                collider.Penetration = Math::Abs(distanceVector.Magnitude() - circle.Radius);

                return collider;
            }
            WATERNION_INLINE static bool IsIntersect(const AABB2D& a, const AABB2D& b) {
                bool outBoundX = a.Max.x < b.Min.x || a.Min.x > b.Max.x;
                bool outBoundY = a.Max.y < b.Min.y || a.Min.y > b.Max.y;
                return !outBoundX && !outBoundY;
            }
        private:
            Collisions() = default;
    };
}