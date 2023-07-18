#pragma once

#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include<stdio.h>

namespace Waternion {
    namespace Editor
    {
        class Editor {
            public:
                virtual ~Editor() = default;
                virtual void OnUpdate(float deltaTime) {}
                virtual void OnRender() {}
                virtual void AddEditor(Editor* editor) {}
                virtual void RemoveEditor(Editor* editor) {}
            protected:
                Editor() : mOpen(true) {}
                bool mOpen;
        };
    } // namespace Editor
} // namespace Waternion