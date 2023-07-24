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

// Components
#include"ECS/Component/Behavior/ScriptComponent.h"
#include"Scripts/PlayerController.h"
#include"Scripts/Background.h"
#include"Scripts/Ball.h"
#include"Scripts/GameLevel.h"
#include"Scripts/Powers/PowerManager.h"
#include"Scripts/GameManager.h"

namespace Waternion
{
    using namespace ECS;

    GameScene::GameScene() : Scene() {
    }

    bool GameScene::Init() {
        Scene::RegisterSystem<InputSystem>();
        Scene::RegisterSystem<SpriteRenderer>();
        Scene::RegisterSystem<BatchRenderer>();
        Scene::RegisterSystem<ScriptingSystem>();
        Scene::RegisterSystem<PhysicWorld>();
        Scene::RegisterSystem<ParticleSystem>();
        Scene::RegisterSystem<AudioSystem>();
        Scene::RegisterSystem<TextRenderer>();

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
    
    void GameScene::Shutdown() {
        for (auto& [_, system] : mSystemsMap) {
            system->Shutdown();
        }
    }

    void GameScene::Load() {
        Shared<Entity> player = MakeShared<Entity>("Paddle");
        player->AddComponent<ScriptComponent>()->Bind<PlayerController>();

        Shared<Entity> background = MakeShared<Entity>("Background");
        background->AddComponent<ScriptComponent>()->Bind<Background>();

        Shared<Entity> ball = MakeShared<Entity>("Ball");
        ball->AddComponent<ScriptComponent>()->Bind<Ball>();

        Shared<Entity> powerManager = MakeShared<Entity>("PowerManager");
        powerManager->AddComponent<ScriptComponent>()->Bind<PowerManager>();

        Shared<Entity> gameManager = MakeShared<Entity>("GameManager");
        gameManager->AddComponent<ScriptComponent>()->Bind<GameManager>();

        uint32_t windowWidth = Application::GetInstance()->GetWindowWidth();
        uint32_t windowHeight = Application::GetInstance()->GetWindowHeight();
        Shared<Entity> gameLevel = MakeShared<Entity>("GameLevel");
        gameLevel->AddComponent<ScriptComponent>()->Bind<GameLevel>();
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(0, "assets/levels/one.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(1, "assets/levels/two.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(2, "assets/levels/three.lvl", windowWidth, windowHeight);
        gameLevel->GetComponent<ScriptComponent>()->GetInstance<GameLevel>()->LoadLevel(3, "assets/levels/four.lvl", windowWidth, windowHeight);
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
        GetSystem<SpriteRenderer>()->BeginScene(deltaTime);
    }
    
    void GameScene::Render(float deltaTime) {
        mPostProcessor->BeginRender();
        GetSystem<SpriteRenderer>()->Draw(deltaTime);
        GetSystem<TextRenderer>()->Draw(deltaTime);
        mPostProcessor->EndRender();
        mPostProcessor->Render(deltaTime);
    }
    
    void GameScene::EndScene(float deltaTime) {
        GetSystem<SpriteRenderer>()->EndScene(deltaTime);
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