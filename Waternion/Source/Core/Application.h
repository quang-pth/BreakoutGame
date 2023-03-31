#pragma once

#include"pch.h"
#include"Window/Window.h"
#include"ECS/Coordinator.h"
#include"ECS/Scene/Scene.h"

namespace Waternion {
    struct WindowConfig {
        int Width = 0;
        int Height = 0;
        std::string Title;
        std::string Version;
    };

    class Application {
        public:
            WATERNION_API static Shared<Application> GetInstance();
            WATERNION_API bool InitWindow(int width, int height, const std::string& title, const std::string& version);
            WATERNION_API void Run();
            WATERNION_API void Shutdown();
            WATERNION_INLINE Shared<ECS::Coordinator> GetCoordinator() { return mCoordinator; }
            WATERNION_INLINE Shared<ECS::Scene> GetScene() { return mScene; }
        private:
            Application();
            void LoadData();
            void ProcessInput();
            void Update(float deltaTime);
            void Render(float deltaTime);
        private:
            Unique<Window> mWindow;
            Shared<ECS::Coordinator> mCoordinator;
            Shared<ECS::Scene> mScene;
    };
} 