#include"Scene.h"
#include"Core/Application.h"

namespace Waternion {
    namespace ECS
    {
        Scene::Scene() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
            WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");
        }

        bool Scene::Load() {
            Shared<Entity> entity;
            entity.reset(new Entity());
            this->RegisterSystem<InputSystem>();
            
            if (!this->InitSystems()) {
                return false;
            }            

            return true;
        }

        void Scene::Shutdown() {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->Shutdown();
                }
            }
        }

        void Scene::Start() {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->Start();
                }
            }
        }

        void Scene::Update(float deltaTime) {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->Update(deltaTime);
                }
            }
        }

        void Scene::Render(float deltaTime) {

        }

        bool Scene::InitSystems() {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    if (!system->Init()) {
                        return false; 
                    }                    
                }
            }

            return true;
        }
    } // namespace ECS
} // namespace Waternion