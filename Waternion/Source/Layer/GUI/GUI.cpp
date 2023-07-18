#include"GUI.h"
#include"pch.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include"Core/Application.h"
#include"Render/PostProcessor.h"
#include"Render/Framebuffer.h"

#include"Layer/GUI/Editors/DockSpace.h"
#include"Layer/GUI/Editors/GameViewport.h"
#include"Layer/GUI/Editors/DebugConsole.h"
#include"Layer/GUI/Editors/DemoSpace.h"

namespace Waternion
{
    GUI::GUI() : Layer(), mEditor() {
    }

    bool GUI::Init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsClassic();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        WATERNION_ASSERT(Window::sInstance != nullptr && "Window context is not initialized");        
        ImGui_ImplGlfw_InitForOpenGL(Window::sInstance, true);
        if (!ImGui_ImplOpenGL3_Init("#version 330")) {
            WATERNION_LOG_ERROR("Failed to init GUI");
            return false;
        }

        WATERNION_LOG_INFO("Init GUI successfully");

        mEditor.reset(new Editor::DockSpace());
        mEditor->AddEditor(new Editor::GameViewport());
        mEditor->AddEditor(new Editor::DebugConsole());
        mEditor->AddEditor(new Editor::DemoSpace());

        return true;
    }

    void GUI::Shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUI::Update(float deltaTime) {
        mEditor->OnUpdate(deltaTime);
    }

    void GUI::Render() {
        mEditor->OnRender();
    }

    void GUI::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GUI::End() {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Window::sInstance, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
} // namespace Waternion