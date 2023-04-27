#include"TextComponent.h"

#include"Core/Application.h"

#include"Core/Manager/ResourceManager.h"
#include"Render/Shader.h"
#include"ECS/System/TextRenderer.h"

namespace Waternion
{
    namespace ECS {
        TextComponent::TextComponent(uint32_t width, uint32_t height) : Component() {
            mShader = ResourceManager::LoadShader("assets/shaders/text_vs.glsl", "assets/shaders/text_fs.glsl", "", "TextShader");
            mShader->Use();
            const Math::Matrix4& ortho = Math::Matrix4::CreateOrtho(width, height, -1.0f, 100.0f);
            mShader->SetMatrix4("Projection", ortho);
            mShader->SetInt("text", 0);
            glGenVertexArrays(1, &mVAO);
            glGenBuffers(1, &mVBO);
            glBindVertexArray(mVAO);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            mTextRenderer = Application::GetInstance()->GetScene()->GetSystem<TextRenderer>();
        }

        void TextComponent::Draw(float deltaTime) {
            mShader->Use();
            mShader->SetVector3("Color", mText.Color);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(mVAO);

            std::string::const_iterator c;
            float x = mText.Position.x;
            float y = mText.Position.y;
            for (c = mText.Value.begin(); c != mText.Value.end(); c++)
            {
                Character ch = mCharacterMap[*c];

                float xpos = x + ch.Bearing.x * mText.Scale;
                float ypos = y - (ch.Size.y - ch.Bearing.y) * mText.Scale;
                
                float w = ch.Size.x * mText.Scale;
                float h = ch.Size.y * mText.Scale;

                float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }
                };

                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glBindBuffer(GL_ARRAY_BUFFER, mVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                x += (ch.Advance >> 6) * mText.Scale; 
            }

            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void TextComponent::SetFont(const std::string& font, uint32_t size) {
            mCharacterMap = mTextRenderer->LoadFont(font, size); 
        }

        void TextComponent::SetText(const std::string& text, const Math::Vector2& position, float scale, const Math::Vector3& color) {
            mText = {text, position, scale, color};
        }

        void TextComponent::SetText(const std::string& text) {
            mText.Value = text;
        }

        void TextComponent::SetPosition(const Math::Vector2& position) {
            mText.Position = position;
        }

        void TextComponent::SetScale(float scale) {
            mText.Scale = scale;
        }

        void TextComponent::SetColor(const Math::Vector3& color) {
            mText.Color = color;
        }
    }
} // namespace Waternion