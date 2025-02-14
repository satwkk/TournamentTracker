#include "Window.h"
#include "Layer.h"
#include <iostream>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

bool CreateWindow(const WindowData& Data, Window& OutWindowHandle)
{
	Window wnd = {};
	wnd.Data = Data;
	
	auto* windowHandle = glfwCreateWindow(wnd.Data.Width, wnd.Data.Height, wnd.Data.Name, nullptr, nullptr);

	if (!windowHandle)
	{
		std::cerr << "Window creation failed" << std::endl;
		return false;
	}

	wnd.GlfwHandle = windowHandle;
	glfwMakeContextCurrent(wnd.GlfwHandle);
	glfwSwapInterval(1);

	OutWindowHandle = wnd;

	return true;
}

void PushLayer(Window& Handle, Layer& NewLayer)
{
	Handle.LayerData.LayerStack.push_back(NewLayer);
}

void UpdateWindowLayers(const Window& Handle)
{
	UpdateLayer(Handle, Handle.LayerData.LayerStack[Handle.LayerData.CurrentLayerIndex]);
}

void UpdateWindow(const Window& Handle)
{
	while (!glfwWindowShouldClose(Handle.GlfwHandle))
	{
		glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(Handle.GlfwHandle, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		UpdateWindowLayers(Handle);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(Handle.GlfwHandle);
	}

	glfwDestroyWindow(Handle.GlfwHandle);
	glfwTerminate();
}

void RenderWindowNextLayer(Window& Handle)
{
	Handle.LayerData.CurrentLayerIndex = (Handle.LayerData.CurrentLayerIndex + 1) % Handle.LayerData.LayerStack.size();
}

void RenderWindowPreviousLayer(Window& Handle)
{
	if (--Handle.LayerData.CurrentLayerIndex < 0)
	{
		Handle.LayerData.CurrentLayerIndex = Handle.LayerData.LayerStack.size() - 1;
	}

}
