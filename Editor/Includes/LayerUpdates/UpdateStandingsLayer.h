#pragma once

#include <vector>

#include "AppContext.h"
#include "Window.h"

static void UpdateLayer_Standings(const Window& Handle)
{
	ImGui::Begin("Standings", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoNavInputs);

	ImVec2 windowSize = {};
	GetWindowSize(Handle, windowSize);
	ImGui::SetWindowSize(windowSize);

	ImGui::SetWindowPos(ImVec2(0, 0));

	// Menu bar
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Statistics"))
			{
				if (ImGui::MenuItem("Add Statistics"))
				{
					if (ImGui::BeginPopupContextWindow("Statistics"))
					{
						ImGui::EndPopup();
					}
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	// Editable league table
	{
		if (ImGui::BeginTable("StandingsTable", 4))
		{
			ImGui::TableSetupColumn("TeamName");

			// Draw the headers
			ImGui::TableNextRow();

			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Team Name");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text("Wins");

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Loss");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text("Draws");

			for (uint32_t i = 0; Context != nullptr && i < Context->NumRegisteredTeams; i++)
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%s", Context->RegisteredTeams[i].TeamName.c_str());

				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%s", std::to_string(Context->RegisteredTeams[i].Statistics.NumWins).c_str());

				ImGui::TableSetColumnIndex(2);
				ImGui::Text("%s", std::to_string(Context->RegisteredTeams[i].Statistics.NumLoss).c_str());

				ImGui::TableSetColumnIndex(3);
				ImGui::Text("%s", std::to_string(Context->RegisteredTeams[i].Statistics.NumDraw).c_str());
			}

			ImGui::EndTable();
		}
	}

	ImGui::End();
}
