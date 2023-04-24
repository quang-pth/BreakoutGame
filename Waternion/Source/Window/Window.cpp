#include"Window.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/TextRenderer.h"

namespace Waternion {
    static InputState state;
    static Shared<Application> application;

    static void PrepareInputStates() {
        memcpy(state.Keyboard.PreviousState, state.Keyboard.CurrentState, NUM_KEYS);
        memset(state.Keyboard.CurrentState, false, NUM_KEYS);
    }

    static void ResizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (key >= 0 && key <= 1024) {
                state.Keyboard.CurrentState[key] = true;
            }
        }
    }

    bool Window::Init(uint32_t width, uint32_t height, const std::string& name) {
        mWidth = width;
        mHeight = height;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

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

        application = Application::GetInstance();
        WATERNION_LOG_INFO("Init Window Successfully!");
        return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    void Window::PollInputEvents() {
        PrepareInputStates();
        glfwPollEvents();
        application->GetScene()->GetSystem<ECS::InputSystem>()->ProcessInput(state);
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(mInstance);
    }
}