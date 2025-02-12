#pragma once

#include "LayerUpdates/UpdateMainLayer.h"
#include "LayerUpdates/UpdateLayerMainMenu.h"

static void(*UpdateMainLayer)(const Window& Handle) = UpdateLayer_Main;
static void(*UpdateMainMenuLayer)(const Window& Handle) = UpdateLayer_MainMenu;
