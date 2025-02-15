#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "RNG.h"
#include "AppContext.h"
#include "Layer.h"
#include "Window.h"
#include "UpdateLayers.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int InitApp()
{
    if (!glfwInit())
        return -1;

    glfwSetErrorCallback(glfw_error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

void InitImguiContext(const Window& Handle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Handle.GlfwHandle, true);

    ImGui_ImplOpenGL3_Init("#version 130");
}

int main(int argc, char** argv)
{
    AppContext Context = {};

    if (!InitApp())
    {
        std::cerr << "App initialization failed" << std::endl;
        return -1;
    }

    WindowData data = {};
    data.Height = 600.f;
    data.Width = 800.f;
    data.Name = "Tournament Tracker";

    Window mainWindow = {};
    if (!CreateWindow(data, mainWindow))
    {
        std::cerr << "Window creation failed" << std::endl;
        return -1;
    }

    glfwSetWindowUserPointer(mainWindow.GlfwHandle, &Context);
    InitImguiContext(mainWindow);

    // Create layers
    std::map<std::string, Layer> LayerMap = {
        { "MainLayer",          CreateLayer("MainLayer", 0.f, 0.f, 20.f, 20.f, UpdateMainLayer) },
        { "MainMenuLayer",      CreateLayer("MainMenuLayer", 0.f, 0.f, 20.f, 20.f, UpdateMainMenuLayer) },
        { "Standings",          CreateLayer("Standings", 0.f, 0.f, 20.f, 20.f, UpdateStandingsLayer) },
    };

    //PushLayer(mainWindow, LayerMap["MainLayer"]);
    PushLayer(mainWindow, LayerMap["MainMenuLayer"]);
    PushLayer(mainWindow, LayerMap["Standings"]);

    // CONTEXT INITIALIZATION, DO IT AT LAST WHEN EVERYTHING IS INITIALIZED
    Context.MainWindowHandle = &mainWindow;
    UpdateWindow(mainWindow);

    return 0;
}