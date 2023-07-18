#include"DebugConsole.h"

#include<imgui_internal.h>

namespace Waternion::Editor
{
    DebugConsole::DebugConsole() : Editor() {

    }
    
    void DebugConsole::OnRender() {
        ImGuiContext& g = *GImGui;
        if (!(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSize)) {
            ImGui::SetNextWindowSize(ImVec2(0.0f, ImGui::GetFontSize() * 12.0f), ImGuiCond_FirstUseEver);
        }
     
        if (!ImGui::Begin("Dear ImGui Debug Log", &mOpen) || ImGui::GetCurrentWindow()->BeginCount > 1)
        {
            ImGui::End();
            return;
        }

        ImGui::CheckboxFlags("All", &g.DebugLogFlags, ImGuiDebugLogFlags_EventMask_);
        ImGui::SameLine(); ImGui::CheckboxFlags("ActiveId", &g.DebugLogFlags, ImGuiDebugLogFlags_EventActiveId);
        ImGui::SameLine(); ImGui::CheckboxFlags("Focus", &g.DebugLogFlags, ImGuiDebugLogFlags_EventFocus);
        ImGui::SameLine(); ImGui::CheckboxFlags("Popup", &g.DebugLogFlags, ImGuiDebugLogFlags_EventPopup);
        ImGui::SameLine(); ImGui::CheckboxFlags("Nav", &g.DebugLogFlags, ImGuiDebugLogFlags_EventNav);
        ImGui::SameLine(); if (ImGui::CheckboxFlags("Clipper", &g.DebugLogFlags, ImGuiDebugLogFlags_EventClipper)) { g.DebugLogClipperAutoDisableFrames = 2; } if (ImGui::IsItemHovered()) ImGui::SetTooltip("Clipper log auto-disabled after 2 frames");
        //SameLine(); CheckboxFlags("Selection", &g.DebugLogFlags, ImGuiDebugLogFlags_EventSelection);
        ImGui::SameLine(); ImGui::CheckboxFlags("IO", &g.DebugLogFlags, ImGuiDebugLogFlags_EventIO);
        ImGui::SameLine(); ImGui::CheckboxFlags("Docking", &g.DebugLogFlags, ImGuiDebugLogFlags_EventDocking);
        ImGui::SameLine(); ImGui::CheckboxFlags("Viewport", &g.DebugLogFlags, ImGuiDebugLogFlags_EventViewport);

        if (ImGui::SmallButton("Clear"))
        {
            g.DebugLogBuf.clear();
            g.DebugLogIndex.clear();
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Copy"))
            ImGui::SetClipboardText(g.DebugLogBuf.c_str());

        ImGui::BeginChild("##log", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);

        ImGuiListClipper clipper;
        clipper.Begin(g.DebugLogIndex.size());
        while (clipper.Step())
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char* line_begin = g.DebugLogIndex.get_line_begin(g.DebugLogBuf.c_str(), line_no);
                const char* line_end = g.DebugLogIndex.get_line_end(g.DebugLogBuf.c_str(), line_no);
                ImGui::TextUnformatted(line_begin, line_end);
                ImRect text_rect = g.LastItemData.Rect;
                if (ImGui::IsItemHovered())
                    for (const char* p = line_begin; p <= line_end - 10; p++)
                    {
                        ImGuiID id = 0;
                        if (p[0] != '0' || (p[1] != 'x' && p[1] != 'X') || sscanf(p + 2, "%X", &id) != 1)
                            continue;
                        ImVec2 p0 = ImGui::CalcTextSize(line_begin, p);
                        ImVec2 p1 = ImGui::CalcTextSize(p, p + 10);
                        // g.LastItemData.Rect = ImRect(text_rect.Min + ImVec2(p0.x, 0.0f), text_rect.Min + ImVec2(p0.x + p1.x, p1.y));
                       
                        g.LastItemData.Rect.Min = ImVec2(text_rect.Min.x + p0.x, text_rect.Min.y);
                        g.LastItemData.Rect.Max = ImVec2(text_rect.Min.x + p0.x + p1.x, text_rect.Min.y + p1.y);

                        if (ImGui::IsMouseHoveringRect(g.LastItemData.Rect.Min, g.LastItemData.Rect.Max, true))
                            ImGui::DebugLocateItemOnHover(id);
                        p += 10;
                    }
            }
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        
        ImGui::EndChild();

        ImGui::End();
    }
} // namespace Waternion::Editor