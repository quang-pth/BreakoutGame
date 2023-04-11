#pragma once

#include"Primitive.h"

namespace Waternion {
    class Collisions {
        public:
            static bool IsIntersect(const Circle& circle, const AABB2D& box) {
                Math::Vector2 distanceVector = circle.Center - box.GetCenterPoint();
                const Math::Vector2& boxSize = box.GetSize();
                distanceVector = Math::Vector2::Clamp(distanceVector, -boxSize * 0.5f, boxSize * 0.5f);
                const Math::Vector2& closestPoint = box.GetCenterPoint() + distanceVector;
                return circle.Contains(closestPoint);
            }
            static bool IsIntersect(const AABB2D& box, const Circle& circle) {
                return Collisions::IsIntersect(circle, box);
            }
        private:
            Collisions() = default;
    };
}