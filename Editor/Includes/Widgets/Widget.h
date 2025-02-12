#pragma once

#include <string>
#include <functional>
#include "Window.h"
#include "imgui/imgui.h"

class IWidget
{
public:
	IWidget() = default;
	IWidget(const Window& handle, const std::string& id);
	virtual ~IWidget();

	IWidget(const IWidget&) = delete;
	IWidget& operator=(const IWidget&) = delete;

	virtual void Update();

	void AddWindowFlags(ImGuiWindowFlags flags);
	void RemoveWindowFlags(ImGuiWindowFlags flags);

	static void StartFrame();
	static void EndFrame();

	void SetPosition(const ImVec2& newPos);
	void SetScale(const ImVec2& newScale);

protected:
	ImGuiWindowFlags mWindowFlags;
	Window mRootHandle;
	std::string mID;
	ImVec2 mPosition;
	ImVec2 mScale;
};