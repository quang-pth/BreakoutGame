#pragma once

#include"Defaults.h"
#include"Render/Texture.h"
#include"Render/VertexArray.h"
#include"Render/Shader.h"

#include"Collisions/Primitive.h"

namespace Waternion {
    namespace ECS {
        class SpriteComponent : public Component {
            public:
                SpriteComponent() : Component(), mColor(Math::Vector3(1.0f)), mIsVisible(true), mBox() {}
                SpriteComponent(const SpriteComponent&) = default;
                void Init(const char* filepath, bool alpha, const char* name);
                void Draw(Shared<Shader> shader, float deltaTime = 0.0f);
                float GetWidth() const; 
                float GetHeight() const;
                WATERNION_INLINE void SetSize(const Math::Vector2& size) {
                    mSize = size;
                }
                WATERNION_INLINE void SetColor(const Math::Vector3& color) {
                    this->SetColor(color.x, color.y, color.z);
                }
                WATERNION_INLINE void SetColor(float r, float g, float b) {
                    mColor.x = r;
                    mColor.y = g;
                    mColor.z = b;
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
            private:
                void CheckError();
                Shared<Texture2D> mTexture;
                Shared<VertexArray> mVAO;
                Math::Vector3 mColor;
                Math::Vector2 mSize;
                bool mIsVisible;
                AABB2D mBox;
        };
    }
}