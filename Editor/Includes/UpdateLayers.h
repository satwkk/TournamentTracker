#pragma once

#include "LayerUpdates/UpdateMainLayer.h"
#include "LayerUpdates/UpdateLayerMainMenu.h"
#include "LayerUpdates/UpdateStandingsLayer.h"

static void(*UpdateMainLayer)(const Window& Handle) = UpdateLayer_Main;
static void(*UpdateMainMenuLayer)(const Window& Handle) = UpdateLayer_MainMenu;
static void(*UpdateStandingsLayer)(const Window& Handle) = UpdateLayer_Standings;
