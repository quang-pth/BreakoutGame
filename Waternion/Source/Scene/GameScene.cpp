#include"GameScene.h"
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
#include"ECS/System/BatchRenderer.h"

#include"ECS/Component/Defaults.h"
#include"ECS/Component/Graphics/SpriteComponent.h"

namespace Waternion
{
    using namespace ECS;

    GameScene::GameScene() : Scene() {
        Scene::RegisterSystem<InputSystem>();
        Scene::RegisterSystem<SpriteRenderer>();
        Scene::RegisterSystem<BatchRenderer>();
        Scene::RegisterSystem<ScriptingSystem>();
        Scene::RegisterSystem<PhysicWorld>();
        Scene::RegisterSystem<ParticleSystem>();
        Scene::RegisterSystem<AudioSystem>();
        Scene::RegisterSystem<TextRenderer>();
        mPostProcessor = MakeShared<PostProcessor>();
    }

    bool GameScene::Init() {
        if (!this->InitSystems()) {
            return false;
        }            
        Shared<Shader> postProcessingShader = ResourceManager::LoadShader(Settings::PostProcessingVertexSource, Settings::PostProcessingFragmentSource, "", Settings::PostProcessingShaderName);

        if (!mPostProcessor->Init(postProcessingShader, Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight())) {
            return false;
        }

        return true;
    }
    
    void GameScene::Shutdown() {
        for (auto& [_, system] : mSystemsMap) {
            system->Shutdown();
        }
    }

    void GameScene::Load() {
    }

    void GameScene::Awake() {
        for (auto& [_, system] : mSystemsMap) {
            system->Awake();
        }
    }
    
    void GameScene::Start() {
        for (auto& [_, system] : mSystemsMap) {
            system->Start();
        }
    }
    
    void GameScene::ProcessInput(const InputState& inputState) {
        GetSystem<InputSystem>()->ProcessInput(inputState);
    }
    
    void GameScene::Update(float deltaTime) {
        mPostProcessor->Update(deltaTime);
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
    
    void GameScene::BeginScene(float deltaTime) {
        GetSystem<BatchRenderer>()->BeginScene(deltaTime);
    }
    
    void GameScene::Render(float deltaTime) {
        mPostProcessor->BeginRender();
        GetSystem<BatchRenderer>()->Draw(deltaTime);
        GetSystem<TextRenderer>()->Draw(deltaTime);
        mPostProcessor->EndRender();
        mPostProcessor->Render(deltaTime);
    }
    
    void GameScene::EndScene(float deltaTime) {
        GetSystem<BatchRenderer>()->EndScene(deltaTime);
    }

    bool GameScene::InitSystems() {
        for (auto& [_, system] : mSystemsMap) {
            if (!system->Init()) {
                return false; 
            }                    
        }

        return true;
    }
} // namespace Waternion