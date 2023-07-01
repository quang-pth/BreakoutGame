#pragma once

#include"pch.h"
#include"ECS/Scene/Scene.h"

namespace Waternion {
    class Window {
            friend class Application;
        public:
            static Shared<class EventDispatcher> sEventDispatcher;
        private:
            Window() = default;
            static void PrepareInputStates();
            static void ResizeCallback(GLFWwindow* window, int width, int height);
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
            static bool Init(uint32_t width, uint32_t height, const std::string& title);
            static void Shutdown();
            static void PollInputEvents();
            static void SwapBuffers();
            static bool WindowShouldClose() {
                return StaticCast<bool>(glfwWindowShouldClose(sInstance));
            }
            static uint32_t GetWidth();
            static uint32_t GetHeight();
        private:
            static GLFWwindow* sInstance;
            static struct InputState sInputState; 
    };
}