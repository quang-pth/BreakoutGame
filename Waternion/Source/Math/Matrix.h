#pragma once

#include"Math/Vec.h"
#include"Math/Utils.h"

namespace Waternion
{
    namespace Math
    {
        class Matrix4 {
            public:
                WATERNION_INLINE Matrix4() {
                    *this = Matrix4::Identity;
                }
                explicit WATERNION_INLINE Matrix4(float value[4][4]) {
                    memcpy(mValue, value, sizeof(float) * 16);
                }
                WATERNION_INLINE Matrix4(const Matrix4&) = default;

                WATERNION_INLINE float* operator[](int index) {
                    return mValue[index];
                }

                friend Matrix4 operator*(Matrix4& a, Matrix4& b);
                friend Matrix4 operator*=(Matrix4& a, Matrix4& b);

                const float* GetAsFloatPtr() const {
                    return ReintepretCast<const float*>(&mValue[0][0]);
                }
                
                static WATERNION_INLINE Matrix4 CreateFromScale(float scaleX, float scaleY, float scaleZ) {
                    return Matrix4::CreateFromScale(Vector3(scaleX, scaleY, scaleZ));
                }
                
                static WATERNION_INLINE Matrix4 CreateFromScale(const Vector3& scale) {
                    float value[4][4] = {
                        {scale.x, 0.0f, 0.0f, 0.0f},
                        {0.0f, scale.y, 0.0f, 0.0f},
                        {0.0f, 0.0f, scale.z, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                    };
                    return Matrix4(value);
                }

                static WATERNION_INLINE Matrix4 CreateFromRotationX(float theta) {
                    float value[4][4] = {
                        {1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, Math::Cos(theta), Math::Sin(theta), 0.0f},
                        {0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                    };
                    return Matrix4(value);
                }

                static WATERNION_INLINE Matrix4 CreateFromRotationY(float theta) {
                    float value[4][4] = {
                        {Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {Math::Sin(theta), 0.0f, Math::Cos(theta), 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                    };
                    return Matrix4(value);
                }
                
                static WATERNION_INLINE Matrix4 CreateFromRotationZ(float theta) {
                    float value[4][4] = {
                        {Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f},
                        {-Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f},
                    };
                    return Matrix4(value);
                }

                static WATERNION_INLINE Matrix4 CreateFromTranslation(float x, float y, float z) {
                    return Matrix4::CreateFromTranslation(Vector3(x, y, z));
                }

                static WATERNION_INLINE Matrix4 CreateFromTranslation(const Vector3& translate) {
                    float value[4][4] = {
                        {1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {translate.x, translate.y, translate.z, 1.0f},
                    };
                    return Matrix4(value);
                }

                static WATERNION_INLINE Matrix4 CreateOrtho(float width, float height, float near, float far) {
                    float value[4][4] = {
                        {2.0f / width, 0.0f, 0.0f ,0.0f},
                        {0.0f, 2.0f / height, 0.0f ,0.0f},
                        {0.0f, 0.0f, 1.0f / (far - near), 0.0f},
                        {0.0f, 0.0f, near / (near - far), 1.0f},
                    };
                    return Matrix4(value);
                }

                static WATERNION_INLINE Matrix4 CreateProjection(float width, float height, float near, float far, float fov) {
                    float yScale = Math::Cotan(fov / 2.0f);
                    float xScale = yScale * height / width;
                    float value[4][4] = {
                        {xScale, 0.0f, 0.0f, 0.0f},
                        {0.0f, yScale, 0.0f, 0.0f},
                        {0.0f, 0.0f, far / (far - near), 1.0f},
                        {0.0f, 0.0f, -near * far / (far - near), 0.0f},
                    };
                    return Matrix4(value);
                }
                
                static WATERNION_INLINE Matrix4 CreateSimpleViewProj(float width, float height) {
                    float value[4][4] = {
                        {2.0f / width, 0.0f, 0.0f, 0.0f},
                        {0.0f, 2.0f / height, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 1.0f},
                    };
                    return Matrix4(value);
                }

                static Matrix4 Identity;
            private:
                float mValue[4][4];
        };
    } // namespace Math
        
} // namespace Waternion