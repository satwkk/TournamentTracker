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

int app_init()
{
    if (!glfwInit())
        return -1;

    glfwSetErrorCallback(glfw_error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

void imgui_init(const window& Handle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Handle.glfw_handle, true);

    ImGui_ImplOpenGL3_Init("#version 130");
}

int main(int argc, char** argv)
{
    appcontext ctx = {};

    if (!app_init())
    {
        std::cerr << "App initialization failed" << std::endl;
        return -1;
    }

    window_data data = {};
    data.height = 600.f;
    data.width = 800.f;
    data.name = "Tournament Tracker";

    window main_window = {};
    if (!create_window(data, main_window))
    {
        std::cerr << "Window creation failed" << std::endl;
        return -1;
    }

    glfwSetWindowUserPointer(main_window.glfw_handle, &ctx);
    imgui_init(main_window);

    // Create layers
    std::map<std::string, layer> LayerMap = {
        { "MainLayer",          create_layer("MainLayer", 0.f, 0.f, 20.f, 20.f, UpdateMainLayer) },
        { "MainMenuLayer",      create_layer("MainMenuLayer", 0.f, 0.f, 20.f, 20.f, UpdateMainMenuLayer) },
        { "Standings",          create_layer("Standings", 0.f, 0.f, 20.f, 20.f, UpdateStandingsLayer) },
    };

    //PushLayer(mainWindow, LayerMap["MainLayer"]);
    push_layer(&main_window, LayerMap["MainMenuLayer"]);
    push_layer(&main_window, LayerMap["Standings"]);

    // CONTEXT INITIALIZATION, DO IT AT LAST WHEN EVERYTHING IS INITIALIZED
    ctx.main_window_handle = &main_window;
    update_window(&ctx);

    return 0;
}