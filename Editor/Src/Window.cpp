#include "Window.h"
#include "Layer.h"
#include <iostream>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

bool create_window(const window_data& data, window& out_handle)
{
	window wnd = {};
	wnd.data = data;
	
	auto* handle = glfwCreateWindow(wnd.data.width, wnd.data.height, wnd.data.name, nullptr, nullptr);

	if (!handle)
	{
		std::cerr << "Window creation failed" << std::endl;
		return false;
	}

	wnd.glfw_handle = handle;

	glfwSetWindowSizeLimits(handle, 200, 200, data.width, data.height);
	glfwMakeContextCurrent(wnd.glfw_handle);
	glfwSwapInterval(1);

	out_handle = wnd;

	return true;
}

void push_layer(window* hwnd, layer& new_layer)
{
	hwnd->layer_data.layer_stack.push_back(new_layer);
}

void update_window_layers(appcontext* ctx)
{
	update_layer(ctx, ctx->main_window_handle->layer_data.layer_stack[ctx->main_window_handle->layer_data.current_layer_index]);
}

void update_window(appcontext* ctx)
{
	while (!glfwWindowShouldClose(ctx->main_window_handle->glfw_handle))
	{
		// Poll events
		glfwPollEvents();

		// Update viewport size

        int display_w, display_h;
        glfwGetFramebufferSize(ctx->main_window_handle->glfw_handle, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		// Setup imgui drawing frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Update all layers
		update_window_layers(ctx);

		// Render to imgui viewport
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the buffers
		glfwSwapBuffers(ctx->main_window_handle->glfw_handle);
	}

	glfwDestroyWindow(ctx->main_window_handle->glfw_handle);
	glfwTerminate();
}

void render_next_layer(window* hwnd)
{
	hwnd->layer_data.current_layer_index = (hwnd->layer_data.current_layer_index + 1) % hwnd->layer_data.layer_stack.size();
}

void render_prev_layer(window* hwnd)
{
	if (--hwnd->layer_data.current_layer_index < 0)
	{
		hwnd->layer_data.current_layer_index = hwnd->layer_data.layer_stack.size() - 1;
	}

}
