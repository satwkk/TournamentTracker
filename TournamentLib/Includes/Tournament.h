#pragma once

#include <iostream>
#include <vector>

#define TOURNAMENTFAILED 0
#define TOURNAMENTSUCCESS 1

#define SAFEDIVISION(num, den) \
if (den == 0) return num;\
return num/den;

enum modification_type : uint8_t
{
	WIN, LOSS, DRAW
};

/// <summary>
/// Data representing team statistics
/// </summary>
struct team_statistics
{
	uint32_t n_wins = 0;
	uint32_t n_loss = 0;
	uint32_t n_draw = 0;

	float win_percentage() { SAFEDIVISION(n_wins, n_wins + n_loss + n_draw); }
};

/// <summary>
/// Data representing information about team
/// </summary>
struct team
{
	std::string team_name;
	team_statistics statistics;

	team() = default;
	~team() = default;
};

struct team_pair
{
	team* team_a;
	team* team_b;
};

struct match_day
{
	uint32_t num_matchup_pairs = 0;
	team_pair* matchup_pairs = new team_pair[num_matchup_pairs];
	uint32_t match_day_number = 0;
};

/// <summary>
/// The league table for the tournament
/// </summary>
struct league_table
{
	team* playing_teams = nullptr;

	league_table() = default;
	~league_table() = default;
};

/// <summary>
/// Main Tournament Context that stores application global runtime state information.
/// </summary>
struct tournament
{
	// The teams that are registered for tournament
	team* registered_teams = nullptr;
	uint32_t n_teams = 0;

	// Match days and pairs of team for matchup
	std::vector<match_day> played_match_days{};
	uint32_t current_match_day = 0;
	uint32_t total_match_days = -1;

	league_table table;

	team* begin() { return registered_teams; }
	team* end() { return registered_teams + n_teams; }
};

/// <summary>
/// Initializes the tournament with list of teams and sets other state related information
/// </summary>
/// <param name="teams"> Array of teams to register </param>
/// <param name="size"> Size of team array </param>
/// <param name="matchDays"> Number of match days for this tournament </param>
tournament* init_tournament(team* teamArr, uint32_t size, uint32_t nMatchDays);

/// <summary>
/// Initializes the team array inside tournament context. Does some parsing and cleanup of raw input strings
/// </summary>
/// <param name="teams"> The team array to initialize </param>
/// <param name="size"> Size of the team array </param>
bool init_teams(tournament* ctx, team* src, uint32_t size);

/// <summary>
/// Moves to the next match day and creates pairs of teams to match up against each other
/// </summary>
const match_day& advance_match_day(tournament* ctx);

/// <summary>
/// Modifies the team statistics model inside Team struct
/// </summary>
/// <param name="team"> The team to modify statistics information </param>
/// <param name="type"> What kind of modification we want to do to the statistics table </param>
/// <returns></returns>
const team_statistics* register_statistics(team* Team, modification_type Type);

// ============================================= GETTERS =================================================

static const match_day& get_current_match_day(tournament* ctx) { return ctx->played_match_days.back(); }

// =======================================================================================================

// ====================================== DEBUG STUFFS ==========================================

void print_all_teams(tournament* ctx);
void print_team_stat(const team_statistics* stat);

// ==============================================================================================