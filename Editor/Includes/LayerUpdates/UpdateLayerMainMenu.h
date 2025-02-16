#pragma once

#include <string>
#include "GLFW/glfw3.h"
#include "AppContext.h"
#include <vector>
#include "Tournament.h"

char g_TeamNameBuffer[50];
std::vector<team> registered_teams;

static void UpdateLayer_MainMenu(appcontext* ctx)
{
	{
		ImGui::Begin("Team Creation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavInputs);
		{
			// create team group
			ImGui::Begin("Create Team", nullptr, ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoMove);

			ImGui::SetWindowPos(ImVec2(10.f, 10.f));
			ImGui::SetWindowSize(ImVec2(300.f, 300.f));

			// Enter team name field
			ImGui::Text("Enter team name ");

			ImGui::InputText("Team name", g_TeamNameBuffer, IM_ARRAYSIZE(g_TeamNameBuffer));

			if (ImGui::Button("Register Team"))
			{
				team created_team = {};
				created_team.team_name = std::string{ g_TeamNameBuffer };
				registered_teams.push_back(created_team);

				memset(g_TeamNameBuffer, 0, sizeof(g_TeamNameBuffer));
			}

			if (ImGui::Button("Start Tournament"))
			{
				ctx->tournament_ref = init_tournament(&registered_teams[0], registered_teams.size(), 5);

				if (ctx->tournament_ref != nullptr) 
				{
					advance_match_day(ctx->tournament_ref);
					render_next_layer(ctx->main_window_handle);
				}
			}

			// Registered team table
			{
				ImGui::Begin("Table List");

				if (ImGui::BeginTable("Registered Teams", 1))
				{
					ImGui::TableSetupColumn("Team Name");

					for (uint32_t i = 0; i < registered_teams.size(); i++)
					{
						ImGui::TableNextRow();
						ImGui::TableSetColumnIndex(0);
						ImGui::Text("%s", registered_teams[i].team_name.c_str());

						// Remove team buttons
						if (ImGui::Button(("-##" + std::to_string(i)).c_str()))
						{
							for (auto it = registered_teams.begin(); it != registered_teams.end(); it++)
							{
								if (it->team_name == registered_teams[i].team_name)
								{
									registered_teams.erase(it);
									break;
								}
							}
						}
					}
					ImGui::EndTable();
				}

				ImGui::End();
			}

			ImGui::End();
		}


		ImGui::End();
	}
}
