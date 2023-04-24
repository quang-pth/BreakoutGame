#pragma once

#include"pch.h"
#include"ECS/Scene/Scene.h"

namespace Waternion {
    class Window {
        public:
            WATERNION_INLINE Window() = default;
            WATERNION_INLINE Window(const Window&) = default;
            WATERNION_API bool Init(uint32_t width, uint32_t height, const std::string& title);
            WATERNION_API void Shutdown();
            WATERNION_API void PollInputEvents();
            WATERNION_INLINE bool WindowShouldClose() {
                return StaticCast<bool>(glfwWindowShouldClose(mInstance));
            }
            WATERNION_API void SwapBuffers();
            WATERNION_INLINE uint32_t GetWidth() const { 
                int32_t width, height;
                glfwGetWindowSize(mInstance, &width, &height);
                return width; 
            }
            WATERNION_INLINE uint32_t GetHeight() const { 
                int32_t width, height;
                glfwGetWindowSize(mInstance, &width, &height);
                return height; 
            }
        private:
            GLFWwindow* mInstance;
            uint32_t mWidth, mHeight;
    };
}