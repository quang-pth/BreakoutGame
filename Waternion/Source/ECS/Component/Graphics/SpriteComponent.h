#pragma once

#include"ECS/Component/Defaults.h"
#include"Collisions/Primitive.h"

#include"Render/Texture.h"
#include"Render/VertexArray.h"
#include"Render/Shader.h"

namespace Waternion {
    struct Sprite {
        Shared<class Texture2D> Texture;
        Shared<class VertexArray> VAO;
        Shared<class Shader> Shader;
        Math::Vector4 Color;
        Math::Vector2 Size;
    };

    namespace ECS {
        class SpriteComponent : public Component {
            public:
                SpriteComponent();
                SpriteComponent(const SpriteComponent&) = default;
                virtual void Init(const char* filepath, bool alpha, const char* name);
                virtual void Draw(float deltaTime = 0.0f);
                float GetScaledWidth() const; 
                float GetScaledHeight() const;
                float GetTextureWidth() const;
                float GetTextureHeight() const;
                WATERNION_INLINE void SetSprite(Sprite* sprite) { mSprite = sprite; }
                WATERNION_INLINE void SetSize(const Math::Vector2& size) {
                    mSprite->Size = size;
                }
                WATERNION_INLINE void SetColor(const Math::Vector4& color) {
                    SetColor(color.x, color.y, color.z, color.w);
                }
                WATERNION_INLINE void SetColor(float r, float g, float b, float a) {
                    mSprite->Color.x = r;
                    mSprite->Color.y = g;
                    mSprite->Color.z = b;
                    mSprite->Color.w = a;
                }
                WATERNION_INLINE const Math::Vector4& GetColor() const {
                    return mSprite->Color;
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
                    return mSprite->Shader;
                }
                WATERNION_INLINE Shared<class Texture2D> GetTexture() const {
                    return mSprite->Texture;
                }
                WATERNION_INLINE Shared<class VertexArray> GetVertexArray() const {
                    return mSprite->VAO;
                }
            private:
                Sprite* mSprite;
                bool mIsVisible;
                AABB2D mBox;
        };
    }
}