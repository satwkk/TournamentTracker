#include "Window.h"
#include "Layer.h"
#include <iostream>
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
		UpdateWindowLayers(Handle);
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
