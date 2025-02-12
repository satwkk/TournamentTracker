#pragma once

#include "imgui/imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "Window.h"
#include "Vector2.h"

static void UpdateLayer_Main(const Window& Handle)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Background
    {
        ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoMouseInputs);
        ImVec2 size = {};
        GetWindowSize(Handle, size);

        ImGui::SetWindowPos(ImVec2(0.f, 0.f));
        ImGui::SetWindowSize(size);

        // Welcome text label
        {
            ImGui::Begin("Welcome box", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            ImVec2 pos = ImVec2(size.x / 2.f, size.y / 2.f);
            ImVec2 windowSize = ImGui::GetWindowSize();

            pos.x -= windowSize.x / 2.f;
            pos.y -= windowSize.y / 2.f;

            ImGui::SetWindowPos(pos);
            ImGui::SetWindowFontScale(1.4f);
            ImGui::Text("Welcome to tournament tracker");
            
            // Create tournament button
            if (ImGui::Button("Create Tournament"))
            {
                RenderWindowNextLayer(const_cast<Window&>(Handle));
            }

            ImGui::End();
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
