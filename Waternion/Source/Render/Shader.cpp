#include"Shader.h"

namespace Waternion
{
    Shader::Shader(const char* vertexSrc, const char* fragmentSrc, const char* geometrySrc) {
        uint32_t vertexShader, fragmentShader, geometryShader;
        // Vertex shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);
        bool vertexCompiledSuccess = this->IsValidShader(vertexShader, EShaderType::FragmentShader);        
        // Fragment Shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);
        bool fragmentCompiledSuccess = this->IsValidShader(fragmentShader, EShaderType::FragmentShader);
        // Shader program
        this->ID  = glCreateProgram();
        if (vertexCompiledSuccess && fragmentCompiledSuccess) {
            glAttachShader(this->ID, vertexShader);
            glAttachShader(this->ID, fragmentShader);
        }
        // Compile geometry shader if exist
        if (std::strcmp(geometrySrc, "")) {
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometryShader, 1, &geometrySrc, nullptr);
            glCompileShader(geometryShader);
            if (this->IsValidShader(geometryShader, EShaderType::GeometryShader)) {
                glAttachShader(this->ID, geometryShader);
            }
        }
        glLinkProgram(this->ID);
        this->IsValidShader(this->ID, EShaderType::Program);
        // Free shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (std::strcmp(geometrySrc, "")) {
            glDeleteShader(geometryShader);
        }
    }

    void Shader::Use() {
        glUseProgram(this->ID);
    }

    void Shader::SetBool(const std::string& name, bool value) {
        glUniform1i(glGetUniformLocation(this->ID, name.c_str()), StaticCast<int>(value));
    }

    void Shader::SetInt(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
    }

    void Shader::SetVector2(const std::string& name, float x, float y) {
        glUniform2f(glGetUniformLocation(this->ID, name.c_str()), x, y);
    }

    void Shader::SetVector2(const std::string& name, const Math::Vector2& value) {
        glUniform2fv(glGetUniformLocation(this->ID, name.c_str()), 1, value.GetAsFloatPtr());
    }

    void Shader::SetVector3(const std::string& name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
    }

    void Shader::SetVector3(const std::string& name, const Math::Vector3& value) {
        glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, value.GetAsFloatPtr());
    }

    void Shader::SetMatrix4(const std::string& name, const Math::Matrix4& value) {
        glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_TRUE, value.GetAsFloatPtr());
    }
    
    bool Shader::IsValidShader(uint32_t shader, EShaderType type) {
        int success;
        char infoLog[512];
        switch (type)
        {
        case EShaderType::VertexShader:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                WATERNION_LOG_ERROR("%s compiled failed: %s", "VertexShader", infoLog);
                return false;
            }
            return true;
            break;
        case EShaderType::FragmentShader:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                WATERNION_LOG_ERROR("%s compiled failed: %s", "FragmentShader", infoLog);
                return false;
            }
            return true;
            break;
        case EShaderType::GeometryShader:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                WATERNION_LOG_ERROR("%s compiled failed: %s", "GeometryShader", infoLog);
                return false;
            }
            return true;
            break;
        case EShaderType::Program:
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 512, nullptr, infoLog);
                WATERNION_LOG_ERROR("Shader Program compiled failed: %s", infoLog);
                return false;
            }
            return true;
            break;
        default:
            WATERNION_LOG_ERROR("No shader type matched");
            return false;
        }
    }
} // namespace Waternion