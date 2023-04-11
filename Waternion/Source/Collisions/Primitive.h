#pragma  once

#include"pch.h"
#include"Math/Vec.h"

namespace Waternion
{
    struct Circle {
        Math::Vector2 Center;
        float Radius;
        
        WATERNION_INLINE Circle() {
            Center =  Math::Vector2::Zero;
            Radius = 0.0f;
        }
        
        WATERNION_INLINE bool Contains(const Math::Vector2& point) const {
            return this->DistanceSquared(point) <= Radius * Radius;
        }

        WATERNION_INLINE float DistanceSquared(const Math::Vector2& point) const {
            return (Center - point).MagnitudeSquared();
        }
        
        WATERNION_INLINE float Distance(const Math::Vector2& point) const {
            return (Center - point).Magnitude();
        }
    };

    struct AABB2D {
        Math::Vector2 Min;
        Math::Vector2 Max;
        WATERNION_INLINE AABB2D() {
            this->Empty();
        }
        WATERNION_INLINE AABB2D(const std::vector<Math::Vector2>& points) {
            this->Empty();

        }
        WATERNION_INLINE void Empty() {
            Min.x = Min.y = Math::MAX_NUMERICS;
            Max.x = Max.y = Math::MIN_NUMERICS;
        }
        WATERNION_INLINE void UpdateMinMax(const Math::Vector2& point) {
            Min.x = Math::Min(point.x, Min.x);
            Min.y = Math::Min(point.y, Min.y);
            Max.x = Math::Max(point.x, Max.x);
            Max.y = Math::Max(point.y, Max.y);
        }
        WATERNION_INLINE Math::Vector2 GetSize() const {
            float x = Max.x - Min.x;
            float y = Max.y - Min.y;
            return Math::Vector2(x, y);
        }

        WATERNION_INLINE Math::Vector2 GetCenterPoint() const {
            return (Min + Max) * 0.5f;
        }
        
        WATERNION_INLINE Math::Vector2 GetSizeVector() const {
            return Max - Min;
        }
        
        WATERNION_INLINE Math::Vector2 GetRadiusVector() const {
            return this->GetSizeVector() * 0.5f;
        }
        
        WATERNION_INLINE bool Contains(const Math::Vector2& point) {
            bool inBoundX = point.x >= Min.x && point.x <= Max.x; 
            bool inBoundY = point.y >= Min.y && point.y <= Max.y;
            return inBoundX && inBoundY; 
        }
        
        WATERNION_INLINE float MinDistanceSquared(const Math::Vector2& point) {
            float dx = Math::Max(Min.x - point.x, 0.0f);
            dx = Math::Max(dx, point.x - Max.x);
            float dy = Math::Max(Min.y - point.y, 0.0f);
            dy = Math::Max(dy, point.y - Max.y);
            return dx * dx + dy * dy;
        }
        
        WATERNION_INLINE float MinDistance(const Math::Vector2& point) {
            return Math::Sqrtf(this->MinDistanceSquared(point));
        }
    };
} // namespace Waternion