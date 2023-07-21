#pragma once

#include"pch.h"
#include"Math/Vec.h"

namespace Waternion
{
    class VertexArray {
        public:
            VertexArray() = default;
            VertexArray(const VertexArray&) = default;
            VertexArray(const float* vertices, int32_t numOfVertices, const int32_t* indices = nullptr, int32_t numOfIndices = 0);
            ~VertexArray();
            void Bind();
            void Unbind();
        protected:
            uint32_t mArrayBufferID;
            uint32_t mVertexBufferID;
            uint32_t mIndexBufferID;
    };
} // namespace Waternion