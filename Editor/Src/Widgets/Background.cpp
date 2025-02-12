#include "Widgets/Background.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <iostream>

Background::Background(const Window& handle, const std::string& id)
	: IWidget(handle, id)
{
	AddWindowFlags(ImGuiWindowFlags_NoTitleBar);
	AddWindowFlags(ImGuiWindowFlags_NoMouseInputs);
	ImGui::Begin(id.c_str(), nullptr, mWindowFlags);
}

Background::~Background()
{
	ImGui::End();
}

void Background::Update()
{
	int width = 0, height = 0;
	glfwGetWindowSize(mRootHandle.GlfwHandle, &width, &height);
	SetScale(ImVec2(width, height));

	IWidget::Update();
}
