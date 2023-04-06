#pragma once

#include"ECS/System.h"
#include"Render/Shader.h"

namespace Waternion
{
    namespace ECS {
        class Renderer : public System {
            public:
                WATERNION_INLINE Renderer() : System() {}
                virtual ~Renderer() = default;
                WATERNION_INLINE virtual void Draw(Shared<Shader> shader, float deltaTime = 0.0f) {};
        };

        class SpriteRenderer : public Renderer {
            public:
                WATERNION_INLINE SpriteRenderer() : Renderer() {} 
                WATERNION_INLINE SpriteRenderer(const SpriteRenderer&) = default; 
                virtual bool Init() override;
                virtual void Draw(Shared<Shader> shader, float deltaTime = 0.0f) override;
        };
    }
} // namespace Waternion