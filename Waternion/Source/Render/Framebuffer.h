#pragma once

#include"pch.h"

namespace Waternion
{
    class Framebuffer {
        public:
            Framebuffer();
            ~Framebuffer();
            bool Init(uint32_t width, uint32_t height);
            void Bind();
            void Unbind();
        private:
            uint32_t mID;
            uint32_t mRenderBuffer;
            Unique<class Texture2D> mTexture;
    };
} // namespace Waternion