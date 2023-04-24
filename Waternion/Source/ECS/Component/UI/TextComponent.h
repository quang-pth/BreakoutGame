#pragma once

#include"ECS/Component/Defaults.h"
#include"ECS/System/TextRenderer.h"

namespace Waternion
{
    class Shader;

    namespace ECS {
        class TextComponent : public Component {
            public:
                TextComponent() = default;
                TextComponent(uint32_t width, uint32_t height);
                void Draw(float deltaTime);
                void SetFont(const std::string& font, uint32_t size);
                void SetText(const std::string& text, const Math::Vector2& position, float scale, const Math::Vector3& color);
                void SetText(const std::string& text);
                void SetPosition(const Math::Vector2& position);
                void SetScale(float scale);
                void SetColor(const Math::Vector3& color);
            private:
                struct Text {
                    std::string Value;
                    Math::Vector2 Position;
                    float Scale;
                    Math::Vector3 Color;
                };
                Text mText;
                Shared<Shader> mShader;
                uint32_t mVAO, mVBO;
                Shared<TextRenderer> mTextRenderer;
                std::unordered_map<char, Character> mCharacterMap;
        };
    }
} // namespace Waternion