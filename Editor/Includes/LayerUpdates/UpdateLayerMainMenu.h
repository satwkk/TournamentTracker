#pragma once

#include "GLFW/glfw3.h"
#include "AppContext.h"
#include <vector>
#include "Tournament.h"

char g_TeamNameBuffer[50];

static void UpdateLayer_MainMenu(const Window& Handle)
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

			AppContext* ctx = (AppContext*)glfwGetWindowUserPointer(Handle.GlfwHandle);

			if (ImGui::Button("Register Team"))
			{
				Team team = {};
				team.TeamName = std::string{ g_TeamNameBuffer };
				ctx->RegisteredTeams.push_back(team);

				memset(g_TeamNameBuffer, 0, sizeof(g_TeamNameBuffer));
			}

			if (ImGui::Button("Start Tournament"))
			{
				InitializeTournament(&ctx->RegisteredTeams[0], ctx->RegisteredTeams.size(), 5);
				RenderWindowNextLayer(const_cast<Window&>(Handle));
			}

			// Registered team table
			{
				ImGui::Begin("Table List");

				if (ImGui::BeginTable("Registered Teams", 1))
				{
					ImGui::TableSetupColumn("Team Name");

					for (uint32_t i = 0; i < ctx->RegisteredTeams.size(); i++)
					{
						ImGui::TableNextRow();
						ImGui::TableSetColumnIndex(0);
						ImGui::Text("%s", ctx->RegisteredTeams[i].TeamName.c_str());

						// Remove team buttons
						if (ImGui::Button(("-##" + std::to_string(i)).c_str()))
						{
							for (auto it = ctx->RegisteredTeams.begin(); it != ctx->RegisteredTeams.end(); it++)
							{
								if (it->TeamName == ctx->RegisteredTeams[i].TeamName)
								{
									ctx->RegisteredTeams.erase(it);
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
