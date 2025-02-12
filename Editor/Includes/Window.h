#pragma once

#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Layer.h"

struct GLFWwindow;

struct WindowData
{
	float Height;
	float Width;
	const char* Name;
};

struct LayerData
{
	std::vector<Layer> LayerStack;
	uint32_t CurrentLayerIndex = 0;
};

struct Window
{
	WindowData Data;
	LayerData LayerData;
	GLFWwindow* GlfwHandle;
};

bool CreateWindow(const WindowData& Data, Window& OutWindowHandle);

void PushLayer(Window& Handle, Layer& NewLayer);

void UpdateWindowLayers(const Window& Handle);

void UpdateWindow(const Window& Handle);

void RenderWindowNextLayer(Window& Handle);

void RenderWindowPreviousLayer(Window& Handle);

static void GetWindowSize(const Window& Handle, ImVec2& OutSize)
{
	int width = 0, height = 0;
	glfwGetWindowSize(Handle.GlfwHandle, &width, &height);
	OutSize.x = (float)width;
	OutSize.y = (float)height;
}