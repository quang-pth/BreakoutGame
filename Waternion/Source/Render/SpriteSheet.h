#pragma once

#include"pch.h"

namespace Waternion {
    class SpriteSheet {
        public:
            SpriteSheet();
            SpriteSheet(const std::string& filepath, uint32_t cellWidth, uint32_t cellHeight);
            ~SpriteSheet() = default;
            SpriteSheet(const SpriteSheet&) = default;
            std::vector<struct Sprite*>& GetSprites() {
                return mSprites;
            }
        private:
            std::vector<struct Sprite*> mSprites;
    };
}