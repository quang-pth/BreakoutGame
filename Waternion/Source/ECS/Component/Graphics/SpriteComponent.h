#pragma once

#include"ECS/Component/Defaults.h"
#include"Collisions/Primitive.h"

#include"Render/Texture.h"
#include"Render/VertexArray.h"
#include"Render/Shader.h"

namespace Waternion {
    namespace ECS {
        class WATERNION_API SpriteComponent : public Component {
            public:
                SpriteComponent();
                SpriteComponent(const char* filepath, bool alpha, const char* name);
                SpriteComponent(const SpriteComponent&) = default;
                virtual void Init(const char* filepath, bool alpha, const char* name);
                virtual void Draw(float deltaTime = 0.0f);
                float GetScaledWidth() const; 
                float GetScaledHeight() const;
                float GetTextureWidth() const;
                float GetTextureHeight() const;
                WATERNION_INLINE void SetSize(const Math::Vector2& size) {
                    mSize = size;
                }
                WATERNION_INLINE void SetColor(const Math::Vector4& color) {
                    SetColor(color.x, color.y, color.z, color.w);
                }
                WATERNION_INLINE void SetColor(float r, float g, float b, float a) {
                    mColor.x = r;
                    mColor.y = g;
                    mColor.z = b;
                    mColor.w = a;
                }
                WATERNION_INLINE const Math::Vector4& GetColor() const {
                    return mColor;
                }
                WATERNION_INLINE void SetIsVisible(bool visible) {
                    mIsVisible = visible;
                }
                WATERNION_INLINE bool GetIsVisible() const {
                    return mIsVisible;
                }
                WATERNION_INLINE const AABB2D& GetBox() const {
                    return mBox;
                }
                void SetShader(Shared<class Shader> shader);
                void SetShader(const char* shaderName);
                WATERNION_INLINE Shared<class Shader> GetShader() const {
                    return mShader;
                }
                WATERNION_INLINE Shared<class Texture2D> GetTexture() const {
                    return mTexture;
                }
                WATERNION_INLINE Shared<class VertexArray> GetVertexArray() const {
                    return mVAO;
                }
            private:
                Shared<class Texture2D> mTexture;
                Shared<class VertexArray> mVAO;
                Shared<class Shader> mShader;
                Math::Vector4 mColor;
                Math::Vector2 mSize;
                bool mIsVisible;
                AABB2D mBox;
        };
    }
}