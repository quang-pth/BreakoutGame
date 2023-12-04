#pragma once

#include"ECS/System/Renderer.h"
#include"Render/Batching/RenderBatch.h"

namespace Waternion::ECS
{
    #define MAX_BATCH_SIZE 1000

    class SpriteComponent;

    class WATERNION_API BatchRenderer : public Renderer {
        public:
            BatchRenderer();
            virtual void BeginScene(float deltaTime) override;
            virtual void Draw(float deltaTime) override;
            virtual void EndScene(float deltaTime) override;
            void AddSprite(Shared<SpriteComponent> sprite);
        private:
            std::vector<Shared<RenderBatch>> mRenderBatches; 
    };
} // namespace Waternion::ECS