#pragma once

static void UpdateLayer_MainMenu(const Window& Handle)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Background
	{
		ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoTitleBar);
		ImVec2 size = {};
		GetWindowSize(Handle, size);
		ImGui::SetWindowPos(ImVec2(0.f, 0.f));
		ImGui::SetWindowSize(size);
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
