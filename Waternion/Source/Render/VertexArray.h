#pragma once

#include"pch.h"

namespace Waternion
{
    class VertexArray {
        public:
            VertexArray() = default;
            VertexArray(const VertexArray&) = default;
            VertexArray(const float* vertices, uint32_t numOfVertices, const uint32_t* indices, uint32_t numOfIndices);
            ~VertexArray();
            void Bind();
            void Unbind();
        private:
            uint32_t mArrayBufferID;
            uint32_t mVertexBufferID;
            uint32_t mIndexBufferID;
    };
} // namespace Waternion