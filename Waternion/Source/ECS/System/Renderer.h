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
                WATERNION_INLINE virtual void BeginScene(float deltaTime = 0.0f) {};
                WATERNION_INLINE virtual void Draw(Shared<Shader> shader, float deltaTime = 0.0f) {};
                WATERNION_INLINE virtual void EndScene(float deltaTime = 0.0f) {};
        };

        class SpriteRenderer : public Renderer {
            public:
                WATERNION_INLINE SpriteRenderer() : Renderer() {} 
                WATERNION_INLINE SpriteRenderer(const SpriteRenderer&) = default; 
                virtual bool Init() override;
                virtual void BeginScene(float deltaTime = 0.0f) override;
                virtual void Draw(Shared<Shader> shader, float deltaTime = 0.0f) override;
                virtual void EndScene(float deltaTime = 0.0f) override;
            private:
                std::vector<Shared<class SpriteComponent>> mSprites;
        };
    }
} // namespace Waternion