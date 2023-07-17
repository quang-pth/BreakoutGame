#include"GameViewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include"Window/Window.h"
#include"Core/Application.h"
#include"Render/PostProcessor.h"
#include"Render/Framebuffer.h"

namespace Waternion::Editor {
    GameViewport::GameViewport() : Editor() {

    }

    void GameViewport::OnUpdate(float deltaTime) {

    }

    void GameViewport::OnRender() {
        ImGui::Begin("Game Viewport", &mOpen, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImVec2 viewportSize = this->CalculateViewportSize();
        ImVec2 viewportPosition  = this->CalculateViewportCenterPosition(viewportSize);
        ImGui::SetCursorPos(viewportPosition);
        int framebufferId = Application::GetInstance()->GetScene()->GetPostProcessor()->GetFramebuffer()->GetID();
        ImGui::Image(ImTextureID(framebufferId), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    ImVec2 GameViewport::CalculateViewportSize() {
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        windowSize.x -= ImGui::GetScrollX();
        windowSize.y -= ImGui::GetScrollY();

        float aspectRatio = Application::GetInstance()->GetWindowWidth() / StaticCast<float>(Application::GetInstance()->GetWindowHeight());
        float aspectWidth = windowSize.x;
        float aspectHeight = aspectWidth / aspectRatio;
        if (aspectHeight > windowSize.y) {
            aspectHeight = windowSize.y;
            aspectWidth = aspectHeight * aspectRatio;
        }

        return ImVec2(aspectWidth, aspectHeight);
    }

    ImVec2 GameViewport::CalculateViewportCenterPosition(const ImVec2& viewportSize) {
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        windowSize.x -= ImGui::GetScrollX();
        windowSize.y -= ImGui::GetScrollY();

        float viewportX = (windowSize.x / 2.0f) - (viewportSize.x / 2.0f);
        float viewportY = (windowSize.y / 2.0f) - (viewportSize.y / 2.0f);

        return ImVec2(viewportX + ImGui::GetCursorPosX(), viewportY + ImGui::GetCursorPosY());
    }
}