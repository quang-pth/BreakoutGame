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
                virtual void Draw(Shared<Shader> shader) = 0;
        };

        class SpriteRenderer : public Renderer {
            public:
                WATERNION_INLINE SpriteRenderer() : Renderer() {} 
                WATERNION_INLINE SpriteRenderer(const SpriteRenderer&) = default; 
                virtual bool Init() override;
                virtual void Draw(Shared<Shader> shader) override;
        };
    }
} // namespace Waternion