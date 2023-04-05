#include"VertexArray.h"

namespace Waternion {
    VertexArray::VertexArray(const float* vertices, int32_t numOfVertices, const int32_t* indices, int32_t numOfIndices) {
        // Gen VAO
        glGenVertexArrays(1, &mArrayBufferID);
        glBindVertexArray(mArrayBufferID);
        // Gen VBO
        glGenBuffers(1, &mVertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfVertices, vertices, GL_STATIC_DRAW);
        // Gen EBO
        glGenBuffers(1, &mIndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32_t) * numOfIndices, indices, GL_STATIC_DRAW);
        // Config attribute pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr); // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), ReintepretCast<void*>(3 * sizeof(float))); // Texture coordinates
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray() {
        glDeleteBuffers(1, &mIndexBufferID);
        glDeleteBuffers(1, &mVertexBufferID);
        glDeleteVertexArrays(1, &mArrayBufferID);
    }

    void VertexArray::Bind() {
        glBindVertexArray(mArrayBufferID);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }
}