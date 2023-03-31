#pragma once

#include"pch.h"

namespace Waternion
{
    struct Vector2 {
        float x, y;

        static Vector2 Zero;
        static Vector2 UnitX;
        static Vector2 UnitY;

        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float x, float y) : x(x), y(y) {}
        Vector2(const Vector2&) = default;

        WATERNION_INLINE Vector2 operator+(const Vector2& other) {
            return Vector2(x + other.x, y + other.y);
        }

        WATERNION_INLINE const Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        WATERNION_INLINE Vector2 operator-(const Vector2& other) {
            return Vector2(x - other.x, y - other.y);
        }
        
        WATERNION_INLINE const Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        WATERNION_INLINE Vector2 operator*(float scalar) {
            return Vector2(x * scalar, y * scalar);
        }

        WATERNION_INLINE Vector2 operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        WATERNION_INLINE Vector2 operator/(float scalar) {
            WATERNION_ASSERT(scalar != 0.0f && "Vector divided by zero");
            return Vector2(x / scalar, y / scalar);
        }

        WATERNION_INLINE Vector2 operator/=(float scalar) {
            WATERNION_ASSERT(scalar != 0.0f && "Vector divided by zero");
            x /= scalar;
            y /= scalar;
            return *this;
        }

        WATERNION_INLINE float MagnitudeSquared() {
            return x * x + y * y;
        }    
    
        WATERNION_INLINE float Magnitude() {
            return std::sqrtf(this->MagnitudeSquared());
        }    

        WATERNION_INLINE bool SafeNormalized() {
            float magnitude = this->MagnitudeSquared();
            if (magnitude == 0.0f) {
                return false;
            }

            *this /= this->Magnitude();
            return true;
        }

        WATERNION_INLINE void Normalized() {
            *this /= this->Magnitude();
        }
    }; 
} // namespace Waternion
