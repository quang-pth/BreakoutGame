#pragma once

#include"pch.h"

#include"Render/Shader.h"
#include"Render/Texture.h"

namespace Waternion {
    class ResourceManager
    {
    public:
        static std::unordered_map<std::string, Shared<Shader>> ShadersMap;
        static std::unordered_map<std::string, Shared<Texture2D>> Texture2DsMap;
        // Shader
        static Shared<Shader> LoadShader(const char* vertexPath, const char* fragmentPath,
            const char* geometryPath, const std::string &name);
        static Shared<Shader> GetShader(const std::string& name);
        // Texture
        static Shared<Texture2D> LoadTexture(const char* file, bool alpha, const std::string& name);
        static Shared<Texture2D> GetTexture(const std::string& name);
        // Game Level
        static std::vector<std::vector<uint16_t>> LoadLevel(const char* file);
        static void Clear();
    private:
        // Implement Singleton pattern
        ResourceManager();
        static Shared<Shader> LoadShaderFromFile(const char* vertexPath, const char* fragmentPath, 
            const char* geometryPath = nullptr, const char* name = nullptr);
        static Shared<Texture2D> LoadTextureFromFile(const char* file, bool alpha);
    };
}
