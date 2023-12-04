#include"DockSpace.h"

#include"pch.h"

namespace Waternion::Editor
{
    DockSpace::DockSpace() : Editor(), mOptionFullscreen(true), mOptionPadding(false) {
    }

    void DockSpace::OnUpdate(float deltaTime) {
        for(const Shared<Editor>& editor : mEditors) {
            editor->OnUpdate(deltaTime);
        }
    }

    void DockSpace::OnRender() {
        this->BeginDocking();
        this->RenderEditors();
        this->EndDocking();
    }

    void DockSpace::AddEditor(Editor* editor) {
        Shared<Editor> newEditor;
        newEditor.reset(editor);
        mEditors.emplace_back(newEditor);
    }

    void DockSpace::RemoveEditor(Editor* editor) {
        auto iter = std::find_if(mEditors.begin(), mEditors.end(), [&](const Shared<Editor>& e) {
            return e.get() == editor;
        });
        if (iter != mEditors.end()) {
            mEditors.erase(iter);
        }
    }

    void DockSpace::BeginDocking() {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        
        if (mOptionFullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            window_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (!mOptionPadding) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        }
        
        ImGui::Begin("DockSpace Demo", &mOpen, window_flags);

        if (!mOptionPadding)
            ImGui::PopStyleVar();

        if (mOptionFullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                ImGui::MenuItem("Fullscreen", NULL, &mOptionFullscreen);
                ImGui::MenuItem("Padding", NULL, &mOptionPadding);

                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, &mOpen != nullptr))
                    mOpen = false;

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }


    void DockSpace::EndDocking() {
        ImGui::End();
    }

    void DockSpace::RenderEditors() {
        for(const Shared<Editor>& editor : mEditors) {
            editor->OnRender();
        }
    }
} // namespace Waternion::Editor