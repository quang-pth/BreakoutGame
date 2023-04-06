#include"InputSystem.h"
#include"Core/Application.h"
#include"ECS/Component/Behavior/ScriptComponent.h"

namespace Waternion {
    namespace ECS {
        InputSystem::InputSystem() : System() {
            mName = "InputSystem";
        }

        bool InputSystem::Init() {
            System::Init();
            WATERNION_LOG_INFO("%s initialized successfully!", mName.c_str());
            return true;
        }

        void InputSystem::Shutdown() {
            System::Shutdown();
            WATERNION_LOG_INFO("%s closed!", mName.c_str());
        }

        void InputSystem::Start() {
            System::Start();
        }

        void InputSystem::ProcessInput(const InputState& inputState) {
            for(Shared<Entity> entity : System::GetEntitiesHaveComponent<ScriptComponent>()) {
                Shared<ScriptComponent> script = entity->GetComponent<ScriptComponent>();
                script->OnProcessInput(inputState);
            }
        }
    }
}