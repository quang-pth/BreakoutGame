#pragma once

#include"pch.h"
#include"Window/Window.h"
#include"ECS/Coordinator.h"
#include"Layer/Layer.h"
#include"Scene/SceneManager.h"

namespace Waternion {
    class GameScene;
    class Scene;

    class WATERNION_API Application {
        public:
            Application();
            static Shared<Application> GetInstance();
            virtual bool Init(int width, int height, const std::string& title);
            void Run();
            void Shutdown();
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
            
            template<typename T>
            void AddScene() {
                mSceneManager->AddScene<T>();
            }

            void AddScene(Scene* scene) {
                mSceneManager->AddScene(scene);
            }

        private:
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
            static Shared<Application> sInstance;
        private:
            float mTimeScale;
            Shared<ECS::Coordinator> mCoordinator;
            Shared<SceneManager> mSceneManager;
            std::vector<Shared<Layer>> mLayers;
            bool mIsRunning;
    };

    Application* CreateApplication();
} 