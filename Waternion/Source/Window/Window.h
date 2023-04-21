#pragma once

#include"pch.h"
#include"ECS/Scene/Scene.h"

namespace Waternion {
    class Window {
        public:
            WATERNION_INLINE Window() = default;
            WATERNION_INLINE Window(const Window&) = default;
            WATERNION_API bool Init(int width, int height, const std::string& title);
            WATERNION_API void Shutdown();
            WATERNION_API void PollInputEvents();
            WATERNION_INLINE bool WindowShouldClose() {
                return StaticCast<bool>(glfwWindowShouldClose(mInstance));
            }
            WATERNION_API void SwapBuffers();
            WATERNION_INLINE float GetWidth() const { 
                int32_t width, height;
                glfwGetWindowSize(mInstance, &width, &height);
                return width; 
            }
            WATERNION_INLINE float GetHeight() const { 
                int32_t width, height;
                glfwGetWindowSize(mInstance, &width, &height);
                return height; 
            }
        private:
            GLFWwindow* mInstance;
            float mWidth, mHeight;
    };
}