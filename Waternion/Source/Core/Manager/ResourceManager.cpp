#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Waternion {
    // Init static variables
    std::unordered_map<std::string, Shared<Shader>> ResourceManager::ShadersMap;
    std::unordered_map<std::string, Shared<Texture2D>> ResourceManager::Texture2DsMap;

    Shared<Shader>  ResourceManager::LoadShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const std::string& name)
    {
        if (ShadersMap.find(name) == ShadersMap.end()) {
            ShadersMap[name] = LoadShaderFromFile(vertexPath, fragmentPath, geometryPath, name.c_str());
        }
        return ShadersMap[name];
    }

    Shared<Shader> ResourceManager::GetShader(const std::string& name)
    {
        WATERNION_ASSERT(ShadersMap.count(name) && "Shader was not existed");
        return ShadersMap[name];
    }

    Shared<Texture2D> ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name)
    {
        if (Texture2DsMap.find(name) == Texture2DsMap.end()) {
            Texture2DsMap[name] = LoadTextureFromFile(file, alpha);
        }
        return Texture2DsMap[name];
    }

    Shared<Texture2D> ResourceManager::GetTexture(const std::string& name)
    {
        WATERNION_ASSERT(Texture2DsMap.count(name) && "Texture was not existed");
        return Texture2DsMap[name];
    }

    const std::vector<std::vector<unsigned int>>& ResourceManager::LoadLevel(const char* file)
    {
        std::string line;
        std::ifstream fstream(file);
        
        unsigned int tileCode;
        std::vector<std::vector<unsigned int>> tileData = std::vector<std::vector<unsigned int>>();
        
        if (!fstream.is_open())
        {
            WATERNION_LOG_ERROR("Could not open the file at path %s", file);
        }

        while (std::getline(fstream, line, '\n')) {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }

        return tileData;
    }

    void ResourceManager::Clear()
    {
        // Delete all shaders
        for (auto &shaderIter : ShadersMap) {
            glDeleteShader(shaderIter.second->ID);
        }
        // Delete all textures
        for (auto &textureIter : Texture2DsMap) {
            glDeleteTextures(1, &textureIter.second->ID);
        }
    }

    Shared<Shader> ResourceManager::LoadShaderFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* name)
    {
        // retrieve vertex and fragment source code
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer content into stream
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            
            if (std::strcmp(geometryPath, "")) {
                std::ifstream gShaderFile;
                std::stringstream gShaderStream;
                
                gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                gShaderFile.open(geometryPath);
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
            WATERNION_LOG_INFO("%s shader loaded successfully", name);
        }
        catch (std::ifstream::failure e) {
            WATERNION_LOG_ERROR("Shader compilation failed at path (%s, %s, %s)", vertexPath, fragmentPath, geometryPath);
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        const char* gShaderCode = geometryCode.c_str();
        
        return MakeShared<Shader>(vShaderCode, fShaderCode, geometryPath != nullptr ? gShaderCode : "");
    }

    Shared<Texture2D> ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
    {
        Shared<Texture2D> texture = MakeShared<Texture2D>();
        if (alpha) {
            texture->InternalFormat = GL_RGBA;
            texture->ImageFormat = GL_RGBA;
        }
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = GL_RGB;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;
            texture->InternalFormat = format;
            texture->ImageFormat = format;
            texture->Init(width, height, data);
            WATERNION_LOG_INFO("Texture %s loaded successfully", file);
        }
        else {
            WATERNION_LOG_INFO("====================TEXTURE==================");
            WATERNION_LOG_INFO("Width: %d", width);
            WATERNION_LOG_INFO("Height: %d", height);
            WATERNION_LOG_INFO("Channels: %d", nrChannels);
            WATERNION_LOG_ERROR("Failed to load texture: %s", stbi_failure_reason());
            WATERNION_LOG_INFO("====================TEXTURE==================");
        }

        stbi_image_free(data);
        stbi_set_flip_vertically_on_load(false);
        return texture;
    }
}