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
#include"ECS/System/AudioSystem.h"
#include"ECS/System/TextRenderer.h"

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"

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
            this->RegisterSystem<AudioSystem>();
            this->RegisterSystem<TextRenderer>();
        }

        bool Scene::Load() {
            if (!this->InitSystems()) {
                return false;
            }            

            // Shared<Shader> postProcessingShader = ResourceManager::LoadShader(Settings::PostProcessingVertexSource, Settings::PostProcessingFragmentSource, "", Settings::PostProcessingShaderName);
            // mPostProcessor = MakeShared<PostProcessor>();
            // if (!mPostProcessor->Init(postProcessingShader, Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight())) {
            //     return false;
            // }

            return true;
        }

        void Scene::Shutdown() {
            for (auto& [_, system] : mSystemsMap) {
                system->Shutdown();
            }
        }

        void Scene::Awake() {
            for (auto& [_, system] : mSystemsMap) {
                system->Awake();
            }
        }

        void Scene::Start() {
            for (auto& [_, system] : mSystemsMap) {
                system->Start();
            }
        }

        void Scene::ProcessInput(const InputState& inputState) {
            GetSystem<InputSystem>()->ProcessInput(inputState);
        }

        void Scene::Update(float deltaTime) {
            // mPostProcessor->Update(deltaTime);
            for (EntityID id : mCoordinator->GetEntityIDsHaveComponent<TransformComponent>()) {
                MakeShared<Entity>(id, mCoordinator)->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
            for (auto& [_, system] : mSystemsMap) {
                system->PreUpdate(deltaTime);
                system->Update(deltaTime);
                system->PostUpdate(deltaTime);
            }
            for (EntityID id : mCoordinator->GetEntityIDsHaveComponent<TransformComponent>()) {
                MakeShared<Entity>(id, mCoordinator)->GetComponent<TransformComponent>()->UpdateWorldTransform();
            }
        }

        void Scene::BeginScene(float deltaTime) {
            GetSystem<SpriteRenderer>()->BeginScene(deltaTime);
        }

        void Scene::Render(float deltaTime) {
            // mPostProcessor->BeginRender();
            GetSystem<SpriteRenderer>()->Draw(deltaTime);
            GetSystem<TextRenderer>()->Draw(deltaTime);
            GetSystem<AnimationSystem>()->Draw(deltaTime);
            // mPostProcessor->EndRender();
            // mPostProcessor->Render(deltaTime);
        }

        void Scene::EndScene(float deltaTime) {
            GetSystem<SpriteRenderer>()->EndScene(deltaTime);
        }

        bool Scene::InitSystems() {
            for (auto& [_, system] : mSystemsMap) {
                if (!system->Init()) {
                    return false; 
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