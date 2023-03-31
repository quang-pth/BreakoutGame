#pragma once

#include"pch.h"

namespace Waternion {
    class Window {
        public:
            WATERNION_INLINE Window() = default;
            WATERNION_INLINE Window(const Window&) = default;
            WATERNION_API bool Init(int width, int height, const std::string& title);
            WATERNION_API void Shutdown();
            WATERNION_API void ProcessInput();
            WATERNION_INLINE bool WindowShouldClose() {
                return StaticCast<bool>(glfwWindowShouldClose(mInstance));
            }
        private:
            GLFWwindow* mInstance;
    };
}