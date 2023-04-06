#pragma once

#include"Defaults.h"
#include"Render/Texture.h"
#include"Render/VertexArray.h"
#include"Render/Shader.h"

namespace Waternion {
    namespace ECS {
        class SpriteComponent : public Component {
            public:
                SpriteComponent() : Component() {}
                SpriteComponent(const SpriteComponent&) = default;
                void Init(const char* filepath, bool alpha, const char* name);
                void Draw(Shared<Shader> shader, float deltaTime = 0.0f);
            private:
                void CheckError();
                Shared<Texture2D> mTexture;
                Shared<VertexArray> mVAO;
        };
    }
}