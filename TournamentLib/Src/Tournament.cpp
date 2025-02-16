#include <iostream>
#include <stdio.h>
#include <memory>
#include <algorithm>
#include <functional>
#include <random>
#include <math.h>

#include "Tournament.h"
#include "Memory.h"

tournament* init_tournament(team* teamArr, uint32_t size, uint32_t nMatchDays)
{
	tournament* ctx = new tournament;
	ctx->total_match_days = nMatchDays;
	init_teams(ctx, teamArr, size);
	return ctx;
}

bool init_teams(tournament* ctx, team* src, uint32_t size)
{
	ctx->registered_teams = new team[size];
	ctx->n_teams = size;
	mem_map_copy(ctx->registered_teams, src, size * sizeof(team));
	ctx->table.playing_teams = ctx->registered_teams;
	return true;
}

const match_day& advance_match_day(tournament* ctx)
{
	uint32_t currentMatchDay = ++ctx->current_match_day;
	std::cout << "Starting match day " << currentMatchDay << std::endl;

	// Setup math day
	uint32_t n_pairs = ctx->n_teams / 2;
	match_day match_day{};
	match_day.match_day_number = currentMatchDay;
	match_day.matchup_pairs = new team_pair[n_pairs];

	// Copy team pointers for shuffling
	team** team_arr_copy = new team*[ctx->n_teams];
	for (uint32_t i = 0; i < ctx->n_teams; i++)
		team_arr_copy[i] = &ctx->registered_teams[i];

	// Shuffle team array
	std::random_device device{};
	std::mt19937 rng(device());
	std::shuffle(team_arr_copy, team_arr_copy + ctx->n_teams, rng);

	// Create pairs
	int current_idx = 0;
	for (uint32_t i = 0; i + 1 < ctx->n_teams; i += 2)
	{
		if (current_idx >= n_pairs) break;
		team_pair pair{};
		pair.team_a = team_arr_copy[i];
		pair.team_b = team_arr_copy[i + 1];
		match_day.matchup_pairs[current_idx++] = pair;
	}
	match_day.num_matchup_pairs = current_idx;
	ctx->played_match_days.push_back(match_day);
	delete[] team_arr_copy;
	return get_current_match_day(ctx);
}

const team_statistics* register_statistics(team* team, modification_type type)
{
	switch (type)
	{
		case modification_type::WIN:
			team->statistics.n_wins++;
			break;
		case modification_type::LOSS:
			team->statistics.n_loss++;
			break;
		case modification_type::DRAW:
			team->statistics.n_draw++;
			break;
	}
	return &team->statistics;
}

void print_all_teams(tournament* ctx)
{
	for (int i = 0; i < ctx->n_teams; i++)
		std::cout << ctx->registered_teams[i].team_name << std::endl;
}

void print_team_stat(const team_statistics* stat)
{
	std::cout << "WinCount: " << stat->n_wins << std::endl;
	std::cout << "LossCount: " << stat->n_loss<< std::endl;
	std::cout << "DrawCount: " << stat->n_draw << std::endl;
	std::cout << "Win Percentage: " << (float)stat->n_wins / (stat->n_wins + stat->n_loss + stat->n_draw) << std::endl;
}
