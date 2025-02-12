#pragma once

#include <iostream>
#include <vector>

#define TOURNAMENTFAILED 0
#define TOURNAMENTSUCCESS 1

enum EModificationType : uint8_t
{
	WIN, LOSS, DRAW
};

/// <summary>
/// Data representing team statistics
/// </summary>
struct TeamStatistics
{
	uint32_t NumWins = 0;
	uint32_t NumLoss = 0;
	uint32_t NumDraw = 0;

	TeamStatistics() = default;
	~TeamStatistics() = default;

	float WinPercentage() { return NumWins / (NumWins + NumLoss + NumDraw); }
};

/// <summary>
/// Data representing information about team
/// </summary>
struct Team
{
	std::string TeamName;
	TeamStatistics Statistics;

	Team() = default;
	~Team() = default;
};

struct TeamPair
{
	Team* TeamA;
	Team* TeamB;
};

struct MatchDay
{
	uint32_t NumMatchupPairs = 0;
	TeamPair* MatchupPairs = new TeamPair[NumMatchupPairs];
	uint32_t MatchDayNumber = 0;
};

/// <summary>
/// The league table for the tournament
/// </summary>
struct LeagueTable
{
	Team* PlayingTeams = nullptr;

	LeagueTable() = default;
	~LeagueTable() = default;
};

/// <summary>
/// Main Tournament Context that stores application global runtime state information.
/// </summary>
struct Tournament
{
	// The teams that are registered for tournament
	Team* RegisteredTeams = nullptr;
	uint32_t NumRegisteredTeams = 0;

	// Match days and pairs of team for matchup
	std::vector<MatchDay> PlayedMatchDays{};
	uint32_t CurrentMatchDay = 0;
	uint32_t TotalMatchDays = -1;

	LeagueTable Table;
};

extern Tournament* Context;

/// <summary>
/// Initializes the tournament with list of teams and sets other state related information
/// </summary>
/// <param name="teams"> Array of teams to register </param>
/// <param name="size"> Size of team array </param>
/// <param name="matchDays"> Number of match days for this tournament </param>
bool InitializeTournament(Team* Teams, uint32_t Size, uint32_t MatchDays);

/// <summary>
/// Initializes the team array inside tournament context. Does some parsing and cleanup of raw input strings
/// </summary>
/// <param name="teams"> The team array to initialize </param>
/// <param name="size"> Size of the team array </param>
bool InitializeRegisteredTeams(Team* Teams, uint32_t Size);

/// <summary>
/// Moves to the next match day and creates pairs of teams to match up against each other
/// </summary>
const MatchDay& NextMatchDay();

/// <summary>
/// Modifies the team statistics model inside Team struct
/// </summary>
/// <param name="team"> The team to modify statistics information </param>
/// <param name="type"> What kind of modification we want to do to the statistics table </param>
/// <returns></returns>
const TeamStatistics* ModifyTeamStatistics(Team* Team, EModificationType Type);

// ============================================= GETTERS =================================================

static const MatchDay& GetCurrentMatchDay() { return Context->PlayedMatchDays.back(); }

// =======================================================================================================

// ====================================== DEBUG STUFFS ==========================================

void PrintAllTeams();
void PrintTeamStat(const TeamStatistics* Stat);

// ==============================================================================================