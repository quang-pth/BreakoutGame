#pragma once

#include"Render/VertexArray.h"

namespace Waternion {
    namespace ECS {
        class SpriteComponent;
    }

    #define POSITION_ATTRIBUTE 3
    #define COLOR_ATTRIBUTE 4
    #define VERTEX_SIZE 7
    #define QUAD_SIZE (VERTEX_SIZE * sizeof(float))
    #define MAX_VERTICES 1000
    #define QUAD_VERTICES 4
    #define INDICES_PER_QUAD 6

    struct Vertex {
        Math::Vector3 Position;
        Math::Vector4 Color;
    };

    class Shader;

    class RenderBatch : public VertexArray {
        public:
            RenderBatch();
            RenderBatch(uint32_t size);
            bool Init();
            void Render();
            void AddSprite(Shared<ECS::SpriteComponent> sprite);
            bool GetHasSlot() const { return mHasSlot; }
            void SetHasSlot(bool hasSlot) { mHasSlot = hasSlot; }
            void Clear();
        private:
            std::vector<uint32_t> GenerateIndices();
            void uploadSpriteAsVertexProperties(Shared<ECS::SpriteComponent> sprite, uint32_t idx);
        private:
            std::vector<Shared<ECS::SpriteComponent>> mSprites;
            uint32_t mCurrentSpriteIndex;
            bool mHasSlot;
            std::vector<Vertex> mVertices;
            std::vector<uint32_t> mIndices;
            uint32_t mMaxBatchSize;
            Shared<Shader> mShader;
   };
}