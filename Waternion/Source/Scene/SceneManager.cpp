#include"SceneManager.h"

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

#include"Scene/GameScene.h"

namespace Waternion
{
    using namespace ECS;

    SceneManager::SceneManager() : Scene() {

    }

    bool SceneManager::Init() {
        for (Shared<Scene> scene : mScenes) {
            if (!scene->Init()) {
                return false;
            }

            scene->Load();
            scene->Awake();
            scene->Start();
        }

        return true;
    }
    
    void SceneManager::Shutdown() {
        for (const Shared<Scene>& scene : mScenes) {
            scene->Shutdown();
        }
    }

    void SceneManager::Load() {
        for (const Shared<Scene>& scene : mScenes) {
            scene->Load();
        }
    }
    
    void SceneManager::ProcessInput(const InputState& inputState) {
        for (const Shared<Scene>& scene : mScenes) {
            scene->ProcessInput(inputState);
        }
    }
    
    void SceneManager::Update(float deltaTime) {
        for (const Shared<Scene>& scene : mScenes) {
            scene->Update(deltaTime);
        }
    }
    
    void SceneManager::BeginScene(float deltaTime) {
        for (const Shared<Scene>& scene : mScenes) {
            scene->BeginScene(deltaTime);
        }
    }
    
    void SceneManager::Render(float deltaTime) {
        for (const Shared<Scene>& scene : mScenes) {
            scene->Render(deltaTime);
        }
    }
    
    void SceneManager::EndScene(float deltaTime) {
        for (const Shared<Scene>& scene : mScenes) {
            scene->EndScene(deltaTime);
        }
    }
} // namespace Waternion