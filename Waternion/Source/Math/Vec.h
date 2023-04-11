#pragma once

#include"pch.h"
#include"Utils.h"

namespace Waternion
{
    namespace Math {
        struct Vector2 {
            float x, y;

            static Vector2 Zero;
            static Vector2 UnitX;
            static Vector2 UnitY;

            Vector2() : x(0.0f), y(0.0f) {}
            Vector2(float value) : x(value), y(value) {}
            Vector2(float x, float y) : x(x), y(y) {}
            Vector2(const Vector2&) = default;

            friend WATERNION_INLINE Vector2 operator+(const Vector2& a, const Vector2& b) {
                return Vector2(a.x + b.x, a.y + b.y);
            }

            friend WATERNION_INLINE Vector2 operator+=(Vector2& a, const Vector2& b) {
                a = a + b;
                return a;
            }
            
            friend WATERNION_INLINE Vector2 operator-(const Vector2& a, const Vector2& b) {
                return Vector2(a.x - b.x, a.y - b.y);
            }

            friend WATERNION_INLINE Vector2 operator-(const Vector2& a) {
                return Vector2(-a.x, -a.y);
            }

            friend WATERNION_INLINE Vector2 operator-=(Vector2& a, const Vector2& b) {
                a = a - b;
                return a;
            }

            friend WATERNION_INLINE Vector2 operator*(const Vector2& a, float scalar) {
                return Vector2(a.x * scalar, a.y * scalar);
            }

            friend WATERNION_INLINE Vector2 operator*(float scalar, const Vector2& a) {
                return a * scalar;
            }

            friend WATERNION_INLINE Vector2 operator*=(float scalar, Vector2& a) {
                a = scalar * a;
                return a;
            }

            friend WATERNION_INLINE Vector2 operator*=(Vector2& a, float scalar) {
                return scalar *= a;
            }

            friend WATERNION_INLINE Vector2 operator/(const Vector2& a, float scalar) {
                WATERNION_ASSERT(!NearZero(scalar) && "Vector divided by zero");
                return Vector2(a.x / scalar, a.y / scalar);
            }

            friend WATERNION_INLINE Vector2 operator/=(Vector2& a, float scalar) {
                WATERNION_ASSERT(!NearZero(scalar) && "Vector divided by zero");
                a = a / scalar;
                return a;
            }

            friend WATERNION_INLINE bool operator==(const Vector2& a, const Vector2& b) {
                return a.x == b.x && a.y == b.y;
            }

            friend WATERNION_INLINE bool operator!=(const Vector2& a, const Vector2& b) {
                return !(a == b);
            }

            WATERNION_INLINE float MagnitudeSquared() {
                return x * x + y * y;
            }    
        
            WATERNION_INLINE float Magnitude() {
                return Sqrtf(this->MagnitudeSquared());
            }    

            WATERNION_INLINE bool SafeNormalized() {
                float magnitude = this->MagnitudeSquared();
                if (NearZero(magnitude)) {
                    return false;
                }
                *this /= this->Magnitude();
                return true;
            }

            WATERNION_INLINE void Normalized() {
                *this /= this->Magnitude();
            }

            WATERNION_INLINE const float* GetAsFloatPtr() const {
                return ReintepretCast<const float*>(&x);
            }

            static float Dot(const Vector2& a, const Vector2& b) {
                return a.x * b.x + a.y * b.y;
            }

            static Vector2 Reflect(const Vector2& v, const Vector2& n) {
                return v - 2.0f * Vector2::Dot(v, n) * n;
            }

            static Vector2 Clamp(const Vector2& value, const Vector2& lower, const Vector2& upper) {
                Vector2 returnValue = value;
                returnValue.x = Math::Clamp(returnValue.x, lower.x, upper.x);
                returnValue.y = Math::Clamp(returnValue.y, lower.y, upper.y);
                return returnValue;
            }
        };

        struct Vector3 {
            float x, y, z;

            static Vector3 Zero;
            static Vector3 UnitX;
            static Vector3 UnitY;
            static Vector3 UnitZ;

            Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
            Vector3(float value) : x(value), y(value), z(value) {}
            Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
            Vector3(const Vector2& vec2) : x(vec2.x), y(vec2.y), z(0.0f) {}
            Vector3(const Vector3&) = default;

            friend WATERNION_INLINE Vector3 operator+(const Vector3& a, const Vector3& b) {
                return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
            }

            friend WATERNION_INLINE const Vector3& operator+=(Vector3& a, const Vector3& b) {
                a = a + b;
                return a;
            }

            friend WATERNION_INLINE Vector3 operator-(const Vector3& a, const Vector3& b) {
                return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
            }
            
            friend WATERNION_INLINE const Vector3& operator-=(Vector3& a, const Vector3& b) {
                a = a - b;
                return a;
            }

            friend WATERNION_INLINE Vector3 operator*(float scalar, const Vector3& a) {
                return Vector3(a.x * scalar, a.y * scalar, a.z * scalar);
            }

            friend WATERNION_INLINE Vector3 operator*(const Vector3& a, float scalar) {
                return scalar * a;
            }

            friend WATERNION_INLINE Vector3 operator*=(float scalar, Vector3& a) {
                a = a *scalar;
                return a;
            }

            friend WATERNION_INLINE Vector3 operator*=(Vector3& a, float scalar) {
                return scalar *= a;
            }

            friend WATERNION_INLINE Vector3 operator/(const Vector3& a, float scalar) {
                WATERNION_ASSERT(!NearZero(scalar) && "Vector divided by zero");
                return Vector3(a.x / scalar, a.y / scalar, a.z / scalar);
            }

            friend WATERNION_INLINE Vector3 operator/=(Vector3& a, float scalar) {
                WATERNION_ASSERT(!NearZero(scalar) && "Vector divided by zero");
                a = a / scalar;
                return a;
            }

            
            friend WATERNION_INLINE bool operator==(const Vector3& a, const Vector3& b) {
                return a.x == b.x && a.y == b.y && a.z == b.z;
            }

            friend WATERNION_INLINE bool operator!=(const Vector3& a, const Vector3& b) {
                return !(a == b);
            }

            WATERNION_INLINE float MagnitudeSquared() {
                return x * x + y * y + z * z;
            }    
        
            WATERNION_INLINE float Magnitude() {
                return Sqrtf(this->MagnitudeSquared());
            }    

            WATERNION_INLINE bool SafeNormalized() {
                float magnitude = this->MagnitudeSquared();
                if (NearZero(magnitude)) {
                    return false;
                }
                *this /= this->Magnitude();
                return true;
            }

            WATERNION_INLINE void Normalized() {
                *this /= this->Magnitude();
            }

            WATERNION_INLINE const float* GetAsFloatPtr() const {
                return ReintepretCast<const float*>(&x);
            }

            static float Dot(const Vector3& a, const Vector3& b) {
                return a.x * b.x + a.y * b.y + a.z * b.z;
            }

            static Vector3 Cross(const Vector3& a, const Vector3& b)
            {
                Vector3 temp;
                temp.x = a.y * b.z - a.z * b.y;
                temp.y = a.z * b.x - a.x * b.z;
                temp.z = a.x * b.y - a.y * b.x;
                return temp;
            }

            static Vector3 Reflect(const Vector3& v, const Vector3& n) {
                return v - 2.0f * Vector3::Dot(v, n) * n;
            }
        };
    }
} // namespace Waternion
