#include "Widgets/Widget.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

IWidget::IWidget(const Window& handle, const std::string& id)
	: mID(id), mPosition(ImVec2(0.f, 0.f)), mScale(ImVec2(1.f, 1.f)), mRootHandle(handle), mWindowFlags(0)
{
}

IWidget::~IWidget()
{
}

void IWidget::Update()
{
	ImGui::SetWindowPos(mPosition);
	ImGui::SetWindowSize(mScale);
}

void IWidget::AddWindowFlags(ImGuiWindowFlags flags)
{
	mWindowFlags |= flags;
}

void IWidget::RemoveWindowFlags(ImGuiWindowFlags flags)
{
	mWindowFlags &= flags;
}

void IWidget::StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void IWidget::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IWidget::SetPosition(const ImVec2& newPos)
{
	mPosition = newPos;
}

void IWidget::SetScale(const ImVec2& newScale)
{
	mScale = newScale;
}
