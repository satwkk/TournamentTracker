#pragma once

#include "LayerUpdates/UpdateMainLayer.h"
#include "LayerUpdates/UpdateLayerMainMenu.h"
#include "LayerUpdates/UpdateStandingsLayer.h"

static void(*UpdateMainLayer)(appcontext* ctx) = UpdateLayer_Main;
static void(*UpdateMainMenuLayer)(appcontext* ctx) = UpdateLayer_MainMenu;
static void(*UpdateStandingsLayer)(appcontext* ctx) = UpdateLayer_Standings;
