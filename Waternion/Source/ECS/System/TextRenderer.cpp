#include"TextRenderer.h"

#include"ECS/Component/UI/TextComponent.h"

namespace Waternion
{
    namespace ECS
    {
        TextRenderer::TextRenderer() : System(), mFreetype(), mLoadedFonts() {

        }

        bool TextRenderer::Init() {
            if (FT_Init_FreeType(&mFreetype)) {
                WATERNION_LOG_ERROR("TextRenderer is failed to initialize");
                return false;
            }

            WATERNION_LOG_INFO("TextRenderer is initailzed successfully!");
            return true;
        }

        void TextRenderer::Shutdown() {
            WATERNION_LOG_INFO("TextRenderer is closed!");
        }

        void TextRenderer::Draw(float deltaTime) {
            for(Shared<Entity> entity : GetEntitiesHaveComponent<TextComponent>()) {
                entity->GetComponent<TextComponent>()->Draw(deltaTime);
            }
        }

        const std::unordered_map<char, Character>& TextRenderer::LoadFont(const std::string& font, uint32_t size) {
            // Return already loaded font
            if (!mLoadedFonts.empty() && mLoadedFonts.count(font)) {
                return mLoadedFonts.at(font);
            }
            // Loaded new font
            std::unordered_map<char, Character> characters;
            FT_Face face;
            if (FT_New_Face(mFreetype, font.c_str(), 0, &face)) {
                WATERNION_LOG_ERROR("Failed to load font %s", font.c_str());
                return mLoadedFonts[font];
            }

            FT_Set_Pixel_Sizes(face, 0, size);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            for (GLubyte c = 0; c < 128; c++)
            {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    WATERNION_LOG_ERROR("Failed to load glyph %d", c);
                    continue;
                }

                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                Character character = {
                    texture,
                    Math::Vector2(StaticCast<float>(face->glyph->bitmap.width), StaticCast<float>(face->glyph->bitmap.rows)),
                    Math::Vector2(StaticCast<float>(face->glyph->bitmap_left), StaticCast<float>(face->glyph->bitmap_top)),
                    StaticCast<uint32_t>(face->glyph->advance.x)
                };
                characters.insert({c, character});
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            FT_Done_Face(face);
            FT_Done_FreeType(mFreetype);
            
            mLoadedFonts.insert({font, characters});
            return mLoadedFonts.at(font);
        }
    } // namespace ECS
} // namespace Waternion