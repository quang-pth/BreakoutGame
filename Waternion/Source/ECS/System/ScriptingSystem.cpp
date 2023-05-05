#include"ScriptingSystem.h"

#include"ECS/Component/Defaults.h"
#include"ECS/Component/Behavior/ScriptComponent.h"

#include"Window/Window.h"
#include"Core/Event/EventDispatcher.h"

#include"Scripts/Native.h"

namespace Waternion::ECS
{
    ScriptingSystem::ScriptingSystem() : System() {
    }

    bool ScriptingSystem::Init() {
        Window::sEventDispatcher->RegisterCallback<WindowResizedEvent>([&](const WindowResizedEvent& event) {
            for(Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
                entity->GetComponent<ScriptComponent>()->GetInstance<NativeScript>()->OnWindowResized(event);
            }
            return true;
        });

        return true;
    }

    void ScriptingSystem::Awake() {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
            Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
            script->OnAwake();
        }
    }

    void ScriptingSystem::Start() {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
            Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
            script->OnStart();
        }
    }

    void ScriptingSystem::PreUpdate(float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
            Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
            script->OnPreUpdate(deltaTime);
        }
    }

    void ScriptingSystem::Update(float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
            Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
            script->OnUpdate(deltaTime);
        }
    }
    void ScriptingSystem::PostUpdate(float deltaTime) {
        for (Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
            Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
            script->OnPostUpdate(deltaTime);
        }
    }
} // namespace Waternion::ECS