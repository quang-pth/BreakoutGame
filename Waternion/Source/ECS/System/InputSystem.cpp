#include"InputSystem.h"

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
            if (inputState.Keyboard.GetKeyState(GLFW_KEY_W) == ButtonState::EPressed) {
                WATERNION_LOG_INFO("W key pressed");
            }
            if (inputState.Keyboard.GetKeyState(GLFW_KEY_W) == ButtonState::EReleased) {
                WATERNION_LOG_INFO("W key released");
            }
            if (inputState.Keyboard.GetKeyState(GLFW_KEY_W) == ButtonState::EHeld) {
                WATERNION_LOG_INFO("W key held");
            }
            if (inputState.Keyboard.GetKeyState(GLFW_KEY_W) == ButtonState::ENone) {
                WATERNION_LOG_INFO("W key none");
            }
        }
    }
}