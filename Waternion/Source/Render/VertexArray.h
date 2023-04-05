#pragma once

#include"pch.h"

namespace Waternion
{
    class VertexArray {
        public:
            VertexArray() = default;
            VertexArray(const VertexArray&) = default;
            VertexArray(const float* vertices, int32_t numOfVertices, const int32_t* indices, int32_t numOfIndices);
            ~VertexArray();
            void Bind();
            void Unbind();
        private:
            uint32_t mArrayBufferID;
            uint32_t mVertexBufferID;
            uint32_t mIndexBufferID;
    };
} // namespace Waternion