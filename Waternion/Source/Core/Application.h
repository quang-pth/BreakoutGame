#pragma once

#include"pch.h"
#include"Window/Window.h"
#include"ECS/Coordinator.h"
#include"Layer/Layer.h"
#include"Scene/SceneManager.h"

namespace Waternion {
    struct WindowConfig {
        int Width = 0;
        int Height = 0;
        std::string Title;
        std::string Version;
    };

    class GameScene;
    class Scene;

    class Application {
        public:
            WATERNION_API static Shared<Application> GetInstance();
            WATERNION_API bool Init(int width = 1920, int height = 1080, const std::string& title, const std::string& version);
            WATERNION_API void Run();
            WATERNION_API void Shutdown();
            WATERNION_INLINE Shared<ECS::Coordinator> GetCoordinator() { return mCoordinator; }
            
            template<typename T>
            Shared<T> FindScene() {
                WATERNION_STATIC_ASSERT(std::is_base_of<Scene, T>::value);
                return mSceneManager->FindScene<T>();
            }

            WATERNION_INLINE uint32_t GetWindowWidth() { return Window::GetWidth(); }
            WATERNION_INLINE uint32_t GetWindowHeight() { return Window::GetHeight(); }
            WATERNION_INLINE void SetTimeScale(float scale) {
                mTimeScale = scale;
            }
            void PushLayer(Layer* layer);
            void AddScene(Scene* scene);
        private:
            Application();
            void ProcessInput();
            void Update(float deltaTime);
            void Render(float deltaTime);
            template<typename T>
            Shared<T> GetLayer() {
                auto iter = std::find_if(mLayers.begin(), mLayers.end(), [&](const Shared<Layer>& layer) {
                    if (DyanmicPtrCast<T>(layer)) {
                        return true;
                    }

                    return false;
                });

                if (iter != mLayers.end()) {
                    return StaticPtrCast<T>(*iter);
                }

                return nullptr;
            }
        private:
            float mTimeScale;
            Shared<ECS::Coordinator> mCoordinator;
            Shared<SceneManager> mSceneManager;
            std::vector<Shared<Layer>> mLayers;
            bool mIsRunning;
    };

    Application* CreateApplication();
} 