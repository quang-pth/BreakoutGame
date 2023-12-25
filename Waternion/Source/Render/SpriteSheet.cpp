#include"SpriteSheet.h"

#include"Core/Manager/ResourceManager.h"
#include"Render/VertexArray.h"
#include"ECS/Component/Graphics/SpriteComponent.h"
#include"Utils/Settings.h"
#include"Math/Vec.h"

namespace Waternion
{
    SpriteSheet::SpriteSheet() : mSprites() {

    }

    SpriteSheet::SpriteSheet(const std::string& filepath, uint32_t cellWidth, uint32_t cellHeight) : mSprites() {
        Shared<Texture2D> spriteSheetTexture = ResourceManager::LoadTexture(filepath.c_str(), true, filepath);
        int32_t rows = spriteSheetTexture->Height / cellHeight;
        int32_t cols = spriteSheetTexture->Width / cellWidth;

        float yPadding = (float)cellHeight / spriteSheetTexture->Height;
        float xPadding = (float)cellWidth / spriteSheetTexture->Width;
        for (int32_t y = 0; y < rows; y++) {
            for (int32_t x = 0; x < cols; x++) {
                // Bottom-left texture coords
                float x00 = xPadding * x;
                float y00 = yPadding * y;
                // Bottom-right texture coords
                float x10 = x00 + xPadding;
                float y10 = y00;
                // Top-left texture coords
                float x01 = x00;
                float y01 = y00 + yPadding;
                // Top-right texture coords
                float x11 = x00 + xPadding;
                float y11 = y00 + yPadding;

                Vertex vertices[] = {
                    Vertex(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector2(x01, y01)),
                    Vertex(Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(x10, y10)),
                    Vertex(Math::Vector3(0.0f, 0.0f, 0.0f), Math::Vector2(x00, y00)),

                    Vertex(Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector2(x01, y01)),
                    Vertex(Math::Vector3(1.0f, 1.0f, 0.0f), Math::Vector2(x11, y11)),
                    Vertex(Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector2(x10, y10)),
                };
               int32_t numOfVertices = sizeof(vertices) / sizeof(Vertex);
 
                int32_t indices[] = {
                    0, 1, 2, // first triangle
                    3, 4, 5 // second  triangle
                };
                int32_t numOfIndices = sizeof(indices) / sizeof(int32_t);

                Sprite* sprite = new Sprite();
                sprite->VAO = MakeShared<VertexArray>(vertices, numOfVertices, indices, numOfIndices);
                sprite->Shader = ResourceManager::LoadShader(Settings::DefaultVertexSource, Settings::DefaultFragmentSource, "", Settings::DefaultShaderName);
                sprite->Texture = spriteSheetTexture;
                sprite->Color = Math::Vector4(1.0f);
                sprite->Size.x = xPadding;
                sprite->Size.y = yPadding;
                
                mSprites.emplace_back(sprite);
            }
        }
    }
} // namespace Waternion