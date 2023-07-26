#pragma once

#include"pch.h"
#include"Scene.h"

namespace Waternion
{
    class SceneManager : public Scene {
        public:
            SceneManager();
            virtual bool Init() override;
            virtual void Shutdown() override;
            virtual void Load() override;
            virtual void ProcessInput(const InputState&) override;
            virtual void Update(float deltaTime) override;
            virtual void BeginScene(float deltaTime) override;
            virtual void Render(float deltaTime) override;
            virtual void EndScene(float deltaTime) override;
            
            template<typename T>
            void AddScene() {
                WATERNION_STATIC_ASSERT(std::is_base_of<Scene, T>::value);
                mScenes.emplace_back(MakeShared<T>());
            }

            void AddScene(Scene* scene) {
                Shared<Scene> newScene;
                newScene.reset(scene);
                mScenes.emplace_back(newScene);
            }

            template<typename T>
            Shared<T> FindScene() {
                for (Shared<Scene> scene : mScenes) {
                    if (DyanmicPtrCast<T>(scene) != nullptr) {
                        return StaticPtrCast<T>(scene);
                    }
                }

                WATERNION_ASSERT("Scene not found");
                return MakeShared<T>();
            }
        private:
            std::vector<Shared<Scene>> mScenes;
    };
} // namespace Waternion