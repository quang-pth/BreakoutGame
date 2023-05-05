#include"Window.h"
#include"Core/Application.h"
#include"ECS/System/InputSystem.h"
#include"ECS/System/TextRenderer.h"

#include"Core/Event/EventDispatcher.h"

namespace Waternion {
    InputState Window::sInputState;
    Shared<EventDispatcher> Window::sEventDispatcher = MakeShared<EventDispatcher>();
    GLFWwindow* Window::sInstance;

    void Window::PrepareInputStates() {
        memcpy(Window::sInputState.Keyboard.PreviousState, Window::sInputState.Keyboard.CurrentState, NUM_KEYS);
        memset(Window::sInputState.Keyboard.CurrentState, false, NUM_KEYS);
    }

    void Window::ResizeCallback(GLFWwindow* window, int width, int height) {
        Window::sEventDispatcher->Dispatch<WindowResizedEvent>(width, height);
    }

    void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (key >= 0 && key <= 1024) {
                Window::sInputState.Keyboard.CurrentState[key] = true;
            }
            Window::sEventDispatcher->Dispatch<KeyPressedEvent>(key, scancode, action, mode);
        }
    }

    bool Window::Init(uint32_t width, uint32_t height, const std::string& name) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        sInstance = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (sInstance == nullptr) {
            WATERNION_LOG_ERROR("Failed to Init GLFW Window!");
            glfwTerminate();
            return false;
        }

        // Make window context
        glfwMakeContextCurrent(sInstance);
        glfwSetInputMode(sInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Register window callbacks
        glfwSetFramebufferSizeCallback(sInstance, Window::ResizeCallback);
        glfwSetKeyCallback(sInstance, Window::KeyCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            WATERNION_LOG_ERROR("Failed to Init GLAD!");
            return false;
        }
        glViewport(0, 0, width, height);

        WATERNION_LOG_INFO("Init Window Successfully!");
        return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    void Window::PollInputEvents() {
        glfwPollEvents();
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(sInstance);
    }

    uint32_t Window::GetWidth() {
        int32_t width, height;
        glfwGetWindowSize(sInstance, &width, &height);
        return width;
    }

    uint32_t Window::GetHeight() {
        int32_t width, height;
        glfwGetWindowSize(sInstance, &width, &height);
        return height;
    }
}