#pragma once

#include"Math/Vec.h"
#include"ECS/System.h"

namespace Waternion {
    class Shader;

    namespace ECS {
        struct Character {
            uint32_t TextureID;
            Math::Vector2 Size, Bearing;
            uint32_t Advance;
        };

        class TextRenderer : public System {
            public:
                TextRenderer();
                virtual bool Init() override;
                virtual void Shutdown() override;
                void Draw(float deltaTime);
                const std::unordered_map<char, Character>& LoadFont(const std::string& font, uint32_t size);
            private:
                std::unordered_map<std::string, std::unordered_map<char, Character>> mLoadedFonts; 
                FT_Library mFreetype;
        };
    }
}