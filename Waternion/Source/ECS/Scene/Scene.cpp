#include"Scene.h"
#include"Core/Application.h"
#include"Render/Shader.h"
#include"Core/Manager/ResourceManager.h"

// Systems
#include"ECS/System/Renderer.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/ScriptingSystem.h"

// Components
#include"ECS/Component/Defaults.h"
#include"ECS/Component/SpriteComponent.h"
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"ECS/Component/Behavior/MoveComponent.h"
#include"Scripts/PlayerController.h"

namespace Waternion {
    namespace ECS
    {
        Scene::Scene() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
            WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");

            this->RegisterSystem<InputSystem>();
            this->RegisterSystem<SpriteRenderer>();
            this->RegisterSystem<ScriptingSystem>();
        }

        bool Scene::Load() {
            Shared<Entity> entity;
            entity.reset(new Entity());
            entity->GetComponent<TransformComponent>()->SetScale(0.05f);
            entity->AddComponent<MoveComponent>();
            entity->AddComponent<SpriteComponent>()->Init("assets/textures/awesomeface.png", true, "Awesomeface");
            entity->AddComponent<ScriptComponent>()->Bind<PlayerController>();
            
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
                    system->PreUpdate(deltaTime);
                    system->Update(deltaTime);
                    system->PostUpdate(deltaTime);
                }
            }
        }

        void Scene::Render(float deltaTime) {
            Shared<Shader> shader = ResourceManager::LoadShader("assets/shaders/sprite_vs.glsl", "assets/shaders/sprite_fs.glsl", "", "SpriteShader");
            shader->Use();
            const Math::Matrix4& orthoProj = Math::Matrix4::CreateOrtho(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight(), -1.0f, 1000.0f);
            shader->SetMatrix4("Projection", orthoProj);

            for(Shared<System> system : mSystemsMap[GetTypeID<SpriteRenderer>()]) {
                StaticPtrCast<SpriteRenderer>(system)->Draw(shader, deltaTime);
            }
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