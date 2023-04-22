#include"Scene.h"
#include"Core/Application.h"
#include"Render/Shader.h"
#include"Core/Manager/ResourceManager.h"
#include"Render/PostProcessor.h"
#include"Utils/Settings.h"

// Systems
#include"ECS/System/Renderer.h"
#include"ECS/System/ParticleSystem.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/ScriptingSystem.h"
#include"ECS/System/PhysicWorld.h"

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/PlayerController.h"
#include"Scripts/Background.h"
#include"Scripts/Ball.h"
#include"Scripts/GameLevel.h"
#include"Scripts/Powers/PowerManager.h"

namespace Waternion {
    namespace ECS
    {
        Scene::Scene() {
            mCoordinator = Application::GetInstance()->GetCoordinator();
            WATERNION_ASSERT(mCoordinator != nullptr && "Reference Coordinator as nullptr");

            this->RegisterSystem<InputSystem>();
            this->RegisterSystem<SpriteRenderer>();
            this->RegisterSystem<ScriptingSystem>();
            this->RegisterSystem<PhysicWorld>();
            this->RegisterSystem<ParticleSystem>();
        }

        bool Scene::Load() {
            Shared<Entity> player = MakeShared<Entity>("Paddle");
            player->AddComponent<ScriptComponent>()->Bind<PlayerController>();

            Shared<Entity> background = MakeShared<Entity>("Background");
            background->AddComponent<ScriptComponent>()->Bind<Background>();

            Shared<Entity> ball = MakeShared<Entity>("Ball");
            ball->AddComponent<ScriptComponent>()->Bind<Ball>();

            float windowWidth = Application::GetInstance()->GetWindowWidth();
            float windowHeight = Application::GetInstance()->GetWindowHeight();
            Shared<Entity> levelOne = MakeShared<Entity>("LevelOne");
            levelOne->AddComponent<ScriptComponent>()->Bind<GameLevel>();
            levelOne->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel("assets/levels/three.lvl", windowWidth, windowHeight / 2.0f);

            Shared<Entity> powerManager = MakeShared<Entity>("PowerManager");
            powerManager->AddComponent<ScriptComponent>()->Bind<PowerManager>();

            if (!this->InitSystems()) {
                return false;
            }            

            Shared<Shader> postProcessingShader = ResourceManager::LoadShader(Settings::PostProcessingVertexSource, Settings::PostProcessingFragmentSource, "", Settings::PostProcessingShaderName);
            mPostProcessor = MakeShared<PostProcessor>();
            if (!mPostProcessor->Init(postProcessingShader, Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight())) {
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

        void Scene::Awake() {
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->Awake();
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
            mPostProcessor->Update(deltaTime);
            for (EntityID id : mCoordinator->GetEntityIDsHaveComponent<TransformComponent>()) {
                MakeShared<Entity>(id, mCoordinator)->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
            for (auto& [_, systems] : mSystemsMap) {
                for(Shared<System> system : systems) {
                    system->PreUpdate(deltaTime);
                    system->Update(deltaTime);
                    system->PostUpdate(deltaTime);
                }
            }
            for (EntityID id : mCoordinator->GetEntityIDsHaveComponent<TransformComponent>()) {
                MakeShared<Entity>(id, mCoordinator)->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
        }

        void Scene::BeginScene(float deltaTime) {
            for(Shared<System> system : mSystemsMap[GetTypeID<SpriteRenderer>()]) {
                StaticPtrCast<SpriteRenderer>(system)->BeginScene(deltaTime);
            }
        }

        void Scene::Render(float deltaTime) {
            mPostProcessor->BeginRender();
            for(Shared<System> system : mSystemsMap[GetTypeID<SpriteRenderer>()]) {
                StaticPtrCast<SpriteRenderer>(system)->Draw(deltaTime);
            }
            mPostProcessor->EndRender();
            mPostProcessor->Render(deltaTime);
        }

        void Scene::EndScene(float deltaTime) {
            for(Shared<System> system : mSystemsMap[GetTypeID<SpriteRenderer>()]) {
                StaticPtrCast<SpriteRenderer>(system)->EndScene(deltaTime);
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

        Shared<Entity> Scene::FindEntity(const std::string& name) const {
            for (EntityID id : mEntities) {
                Shared<Entity> entity = MakeShared<Entity>(id, mCoordinator);
                Shared<InfoComponent> info = entity->GetComponent<InfoComponent>();
                if (!info->GetName().compare(name)) {
                    return entity;
                }
            }
            WATERNION_ASSERT(false && "Get non-existing entity");
            return MakeShared<Entity>();
        }

        void Scene::AddEntity(EntityID id) {
            WATERNION_ASSERT(id != INVALID_ID && "Add invalid entity");
            mEntities.emplace_back(id);
        }
    } // namespace ECS
} // namespace Waternion