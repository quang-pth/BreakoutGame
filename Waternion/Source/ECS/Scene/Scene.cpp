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
            return true;
        }

        void Scene::Start() {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->Start();
                }
            }
        }

        void Scene::ProcessInput() {
            for(Shared<System> system : mSystemsMap[GetTypeID<InputSystem>()]) {
                StaticPtrCast<InputSystem>(system)->ProcessInput();
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
    } // namespace ECS
} // namespace Waternion