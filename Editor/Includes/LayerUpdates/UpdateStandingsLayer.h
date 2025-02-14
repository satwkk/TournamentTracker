#pragma once

#include <vector>

#include "AppContext.h"
#include "Window.h"

static void UpdateLayer_Standings(const Window& Handle)
{
	ImGui::Begin("Standings");

	// Editable league table
	{
		if (ImGui::BeginTable("StandingsTable", 4))
		{
			ImGui::TableSetupColumn("TeamName");

			for (uint32_t i = 0; Context != nullptr && i < Context->NumRegisteredTeams; i++)
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%s", Context->RegisteredTeams[i].TeamName.c_str());
			}

			ImGui::EndTable();
		}
	}

	ImGui::End();
}
