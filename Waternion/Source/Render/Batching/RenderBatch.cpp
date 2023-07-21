#include"RenderBatch.h"

#include"Core/Manager/ResourceManager.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"Core/Application.h"

namespace Waternion {
    RenderBatch::RenderBatch() : VertexArray() {

    }

    RenderBatch::RenderBatch(uint32_t size) : VertexArray(), mHasSlot(true), mMaxBatchSize(size), 
        mCurrentSpriteIndex(0)  
    {
        mSprites.resize(mMaxBatchSize);

        mVertices.reserve(mMaxBatchSize * QUAD_VERTICES);
        for (int i = 0; i < mMaxBatchSize; i++) {
            mVertices.emplace_back(Vertex());
        }     

        mShader = ResourceManager::LoadShader("assets/shaders/batching_vs.glsl", "assets/shaders/batching_fs.glsl", "", "BatchingShader");
        mShader->Use();
        // const Math::Matrix4& orthoProj = Math::Matrix4::CreateOrtho(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight(), -10.0f, 1000.0f);
        // mShader->SetMatrix4("simpleViewProjection", orthoProj);
        mShader->SetMatrix4("simpleViewProjection", Math::Matrix4::CreateSimpleViewProj(1920, 1080));
    }

    bool RenderBatch::Init() {
        glGenVertexArrays(1, &mArrayBufferID);
        glBindVertexArray(mArrayBufferID);
        glGenBuffers(1, &mVertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_DYNAMIC_DRAW);
        glGenBuffers(1, &mIndexBufferID);
        mIndices = this->GenerateIndices();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, POSITION_ATTRIBUTE, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, COLOR_ATTRIBUTE, GL_FLOAT, GL_FALSE, sizeof(Vertex), ReintepretCast<void*>(offsetof(Vertex, Color)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);

        return true;
    }

    void RenderBatch::Render() {
        glBindVertexArray(mArrayBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size() * sizeof(Vertex), mVertices.data());
        mShader->Use();
        glDrawElements(GL_TRIANGLES, mSprites.size() * INDICES_PER_QUAD, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void RenderBatch::AddSprite(Shared<ECS::SpriteComponent> sprite) {
        uint32_t batchIndex = mCurrentSpriteIndex;
        mSprites[mCurrentSpriteIndex] = sprite;
        this->uploadSpriteAsVertexProperties(sprite, batchIndex * QUAD_VERTICES);
        mCurrentSpriteIndex++;

        if (mCurrentSpriteIndex >= mMaxBatchSize) {
            mHasSlot = false;
        }
    }

    std::vector<uint32_t> RenderBatch::GenerateIndices() {
        uint32_t* indices = new uint32_t[INDICES_PER_QUAD * mMaxBatchSize];

        for (uint32_t i = 0; i < mMaxBatchSize; i++) {
            uint32_t vertexArrayOffset = i * INDICES_PER_QUAD;
            uint32_t vertexQuadOffset = i * QUAD_VERTICES;

            // Create quad indices in counter-clockwise order: 3 2 0 0 2 1
            indices[vertexArrayOffset] = vertexQuadOffset + 3;
            indices[vertexArrayOffset + 1] = vertexQuadOffset + 2;
            indices[vertexArrayOffset + 2] = vertexQuadOffset + 0;
            indices[vertexArrayOffset + 3] = vertexQuadOffset + 0;
            indices[vertexArrayOffset + 4] = vertexQuadOffset + 2;
            indices[vertexArrayOffset + 5] = vertexQuadOffset + 1;
        }

        return std::vector<uint32_t>(indices, indices + INDICES_PER_QUAD * mMaxBatchSize);
    }

    void RenderBatch::uploadSpriteAsVertexProperties(Shared<ECS::SpriteComponent> sprite, uint32_t idx) {
        Math::Vector4 color = sprite->GetColor();

        float xCoordsAlignment = 1.0f;
        float yCoordsAlignment = 1.0f;
        for (int i = 0; i < QUAD_VERTICES; i++) {
            if (i == 1) {
                yCoordsAlignment = 0.0f;
            }
            else if (i == 2) {
                xCoordsAlignment = 0.0f;
            }
            else if (i == 3) {
                yCoordsAlignment = 1.0f;
            }
            
            Shared<ECS::TransformComponent> transform = sprite->GetOwner()->GetComponent<ECS::TransformComponent>();
            Math::Vector3 currentPosition(transform->GetPosition().x + (xCoordsAlignment * transform->GetScale().x),
                    transform->GetPosition().y + (yCoordsAlignment * transform->GetScale().y), transform->GetPosition().z);
            
            mVertices[idx].Position = currentPosition;
            mVertices[idx].Color = color;
            idx++;
        }
    }
}