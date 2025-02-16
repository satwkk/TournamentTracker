#pragma once

#include "imgui/imgui.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Layer.h"

struct GLFWwindow;

typedef GLFWwindow glfw_window;

struct window_data
{
	float height;
	float width;
	const char* name;
};

struct s_layer_data
{
	std::vector<layer> layer_stack;
	uint32_t current_layer_index = 0;
};

struct window
{
	window_data data;
	s_layer_data layer_data;
	glfw_window* glfw_handle;
};

bool create_window(const window_data& data, window& out_handle);

void push_layer(window* hwnd, layer& new_layer);

void update_window_layers(appcontext* ctx);

void update_window(appcontext* ctx);

void render_next_layer(window* hwnd);

void render_prev_layer(window* hwnd);

static void get_window_size(window* handle, ImVec2& out_size)
{
	int width = 0, height = 0;
	glfwGetWindowSize(handle->glfw_handle, &width, &height);
	out_size.x = (float)width;
	out_size.y = (float)height;
}