#pragma once

#include"pch.h"
#include"Math/Matrix.h"

namespace Waternion
{
    enum class EShaderType {
        VertexShader,
        FragmentShader,
        GeometryShader,
        Program
    };

    class Shader {
        public:
            uint32_t ID;
            Shader() = default;
            Shader(const Shader&) = default;
            Shader(const char* vertexSrc, const char* fragmentSrc, const char* geometrySrc);
            void Use();
            // Uniforms
            void SetBool(const std::string& name, bool value);
            void SetInt(const std::string& name, int value);
            void SetFloat(const std::string& name, float value);
            void SetVector2(const std::string& name, float x, float y);
            void SetVector2(const std::string& name, const Math::Vector2& value);
            void SetVector3(const std::string& name, float x, float y, float z);
            void SetVector3(const std::string& name, const Math::Vector3& value);
            void SetMatrix4(const std::string& name, const Math::Matrix4& value);
        private:
            bool IsValidShader(uint32_t shader, EShaderType type);
    };
} // namespace Waternion