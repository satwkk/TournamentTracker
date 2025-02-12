#pragma once

#include <vector>

#include "AppContext.h"
#include "Widgets/Widget.h"
#include "Window.h"

static void UpdateLayer_Standings(const Window& Handle)
{
	IWidget::StartFrame();

	AppContext* ctx = (AppContext*)glfwGetWindowUserPointer(Handle.GlfwHandle);

	ImGui::Begin("Standings");

	// Editable league table
	{
		if (ImGui::BeginTable("StandingsTable", 4))
		{
			ImGui::TableSetupColumn("TeamName");

			for (uint32_t i = 0; i < ctx->RegisteredTeams.size(); i++)
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%s", ctx->RegisteredTeams[i].TeamName.c_str());
			}

			ImGui::EndTable();
		}
	}

	ImGui::End();

	IWidget::EndFrame();
}
