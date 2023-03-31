#pragma once

#include"pch.h"

namespace Waternion {
    struct WindowConfig {
        int Width = 0;
        int Height = 0;
        std::string Title;
        std::string Version;
    };

    class Application {
        public:
            WATERNION_API Application();
            WATERNION_API bool InitWindow(int width, int height, const std::string& title, const std::string& version);
            WATERNION_API void Run();
            WATERNION_API void Shutdown();
        private:
            void ProcessInput();
            void Update(float deltaTime);
            void Render(float deltaTime);
        private:
            WindowConfig mConfig;
            bool mIsRunning;
    };
} 