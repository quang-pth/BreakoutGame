#pragma once

#include"pch.h"

namespace Waternion
{
    namespace Math {
        #define PI 3.14159265
        #define PI_OVER_2 PI / 2
        const float MAX_NUMERICS = std::numeric_limits<float>::infinity();
        const float MIN_NUMERICS = -std::numeric_limits<float>::infinity();

        WATERNION_INLINE float RadsToDegrees(float rads) {
            return rads * 180.0f / PI;
        }

        WATERNION_INLINE float DegreesToRads(float degrees) {
            return degrees * PI / 180.0f;
        }

        template<typename T>
        WATERNION_INLINE T Abs(T value) {
            return std::abs(value);
        }

        WATERNION_INLINE bool NearZero(float value, float epsilon = 0.001f) {
            return Abs<float>(value) <= epsilon;
        }
        
        template<typename T>
        WATERNION_INLINE T Min(const T& a, const T& b) {
            return a < b ? a : b;
        }

        template<typename T>
        WATERNION_INLINE T Max(const T& a, const T& b) {
            return a < b ? b : a;
        }
        
        WATERNION_INLINE float Sqrtf(float value) {
            return std::sqrtf(value);
        }

        WATERNION_INLINE float Fmod(float a, float b) {
            return std::fmodf(a, b);
        }

        template<typename T>
        WATERNION_INLINE T Clamp(const T& value, const T& min, const T& max) {
            return Min<T>(max, Max<T>(min, value));
        }

        template<typename T>
        WATERNION_INLINE T Lerp(const T& from, const T& to, float t) {
            return from + (to - from) * t;
        }

        WATERNION_INLINE float Sin(float angle) {
            return std::sinf(angle);
        }

        WATERNION_INLINE float Cos(float angle) {
            return std::cosf(angle);
        }

        WATERNION_INLINE float Tan(float angle) {
            return std::tanf(angle);
        }

        WATERNION_INLINE float Acos(float angle) {
            return std::acosf(angle);
        }

        WATERNION_INLINE float Atan2(float x, float y) {
            return std::atan2f(y, x);
        }

        WATERNION_INLINE float Cotan(float angle) {
            return 1.0f / Tan(angle);
        }
    }
} // namespace Waternion
