#pragma once

#include <vector>

#include "AppContext.h"
#include "Window.h"

static bool b_show_standings = true;

static void UpdateLayer_Standings(appcontext* ctx)
{
    ImVec2 window_size = {};
    get_window_size(ctx->main_window_handle, window_size);

    if (b_show_standings) {
        ImGui::Begin("Standings", nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMouseInputs);

        ImGui::SetWindowSize(window_size);

        ImGui::SetWindowPos(ImVec2(0, 0));

        // League table
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

                // TODO: Maybe wanna do this some other way, not optimal to sort it every single frame ?
                std::sort(ctx->tournament_ref->begin(), ctx->tournament_ref->end(), [](team a, team b) {
                    return a.statistics.win_percentage() > b.statistics.win_percentage();
                    });

                for (uint32_t i = 0; ctx != nullptr && i < ctx->tournament_ref->n_teams; i++)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", ctx->tournament_ref->table.playing_teams[i].team_name.c_str());

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", std::to_string(ctx->tournament_ref->table.playing_teams[i].statistics.n_wins).c_str());

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", std::to_string(ctx->tournament_ref->table.playing_teams[i].statistics.n_loss).c_str());

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", std::to_string(ctx->tournament_ref->table.playing_teams[i].statistics.n_draw).c_str());
                }

                ImGui::EndTable();
            }
        }

        ImGui::End();
    }

    else {
        // Match days

    }

    // Buttons
    {
        ImGui::Begin("Test", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNavInputs);
        ImGui::SetWindowPos(ImVec2(window_size.x - 200, window_size.y - 50));
        if (ImGui::Button("Standings")) { b_show_standings = true; }
        ImGui::SameLine();
        if (ImGui::Button("Matches")) { b_show_standings = false; }
        ImGui::End();
    }
}
