#include"Window.h"

namespace Waternion {
    static void ResizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (key >= 0 && key <= 1024) {
            // Forward input to Input system
            if (action == GLFW_PRESS) {

            }
            else if (action == GLFW_RELEASE) {

            }
        }
    }

    bool Window::Init(int width, int height, const std::string& name) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // mInstance.reset(glfwCreateWindow(width, height, name.c_str(), NULL, NULL));
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

        WATERNION_LOG_INFO("Init Window Successfully!");
        return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    void Window::ProcessInput() {
        glfwPollEvents();
    }
}