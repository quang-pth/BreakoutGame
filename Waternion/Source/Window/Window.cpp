#include"Window.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"

namespace Waternion {
    static ECS::InputState state;
    static Shared<ECS::Scene> scene;

    static void PreProcess() {
        memcpy(state.Keyboard.PreviousState, state.Keyboard.CurrentState, ECS::NUM_KEYS);
        memset(state.Keyboard.CurrentState, false, ECS::NUM_KEYS);
    }

    static void ResizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        PreProcess();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (key >= 0 && key <= 1024) {
            // Forward input to Input system
            state.Keyboard.CurrentState[key] = true;
            for (Shared<ECS::System> system : scene->GetSystems<ECS::InputSystem>()) {
                StaticPtrCast<ECS::InputSystem>(system)->ProcessInput(state);
            }
        }
    }

    bool Window::Init(int width, int height, const std::string& name) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mInstance = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (mInstance == nullptr) {
            WATERNION_LOG_ERROR("Failed to Init GLFW Window!");
            glfwTerminate();
            return false;
        }

        // Make window context
        glfwMakeContextCurrent(mInstance);
        glfwSetInputMode(mInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Register window callbacks
        glfwSetFramebufferSizeCallback(mInstance, ResizeCallback);
        glfwSetKeyCallback(mInstance, KeyCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            WATERNION_LOG_ERROR("Failed to Init GLAD!");
            return false;
        }

        scene = Application::GetInstance()->GetScene();
        WATERNION_LOG_INFO("Init Window Successfully!");
        return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    void Window::PollInputEvents() {
        glfwPollEvents();
    }
}