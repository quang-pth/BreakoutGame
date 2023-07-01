#pragma once

#include"pch.h"

namespace Waternion
{
    class Texture2D {
        public:
            uint32_t ID;
            uint32_t Width, Height;
            uint32_t InternalFormat;
            uint32_t ImageFormat;
            int32_t WrapS, WrapT;
            int32_t FilterMin, FilterMax;

            Texture2D();
            Texture2D(const Texture2D&) = default;
            void Init(uint32_t width, uint32_t height, const unsigned char* data);
            void Bind();
            void Unbind();
            void Delete();
    };
} // namespace Waternion