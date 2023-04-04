#pragma once

#include"pch.h"
#include"Render/Texture.h"
#include"Render/VertexArray.h"
#include"Render/Shader.h"

namespace Waternion {
    namespace ECS {
        class SpriteComponent {
            public:
                SpriteComponent() = default;
                SpriteComponent(const SpriteComponent&) = default;
                SpriteComponent(const char* filepath, bool alpha, const char* name);
                void Draw(Shared<Shader> shader);
            private:
                Shared<Texture2D> mTexture;
                Shared<VertexArray> mVAO;
        };
    }
}