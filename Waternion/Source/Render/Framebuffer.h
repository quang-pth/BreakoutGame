#pragma once

#include"pch.h"
#include"Texture.h"

namespace Waternion
{
    class Framebuffer {
        public:
            Framebuffer();
            ~Framebuffer();
            bool Init(uint32_t width, uint32_t height);
            void Bind();
            void Unbind();
            void Clear();
            WATERNION_INLINE uint32_t GetID() {
                return mTexture->ID;
            }
        private:
            uint32_t mID;
            uint32_t mRenderBuffer;
            Unique<Texture2D> mTexture;
    };
} // namespace Waternion