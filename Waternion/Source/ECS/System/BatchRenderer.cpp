#include"BatchRenderer.h"

#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion::ECS
{
    BatchRenderer::BatchRenderer() : Renderer(), mRenderBatches() {
    }

    void BatchRenderer::BeginScene(float deltaTime) {
        
    }

    void BatchRenderer::Draw(float deltaTime) {
        for (const Shared<RenderBatch>& batch : mRenderBatches) {
            batch->Render();
        }
    }

    void BatchRenderer::EndScene(float deltaTime) {
       
    }

    void BatchRenderer::AddSprite(Shared<SpriteComponent> sprite) {
        bool isSpriteAdded = false;
        for (const Shared<RenderBatch>& batch : mRenderBatches) {
            if (batch->GetHasSlot()) {
                batch->AddSprite(sprite);
                isSpriteAdded = true;
                break;                
            }
        }

        if (!isSpriteAdded) {
            mRenderBatches.emplace_back(MakeShared<RenderBatch>(MAX_BATCH_SIZE));
            if (mRenderBatches.back()->Init()) {
                mRenderBatches.back()->AddSprite(sprite);
            }
        }
    }
} // namespace Waternion::ECS