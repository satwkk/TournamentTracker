#pragma once
#include <iostream>

#define TOURNAMENTFAILED 0
#define TOURNAMENTSUCCESS 1

#define MAXTEAMS 10

struct Team
{
    char* Name;
};

struct TeamPair
{
    Team* TeamA;
    Team* TeamB;
};

struct Match
{
    TeamPair Teams;
    Team WinningTeam;
    Team LosingTeam;
};

enum TournamentType : uint8_t
{
    LeaguePlay = 1,
    Elimination = 2
};

struct Tournament
{
    // Team data
    Team ParticipatingTeams[MAXTEAMS];
    uint32_t NumTeamsRegistered;

    // Match data
    Match* Matches;
    uint32_t TotalMatches;
    uint32_t TotalRounds;

    // State data
    TournamentType Type;
    bool IsInitialized = false;
    bool IsFinished()
    {
        return (sizeof(Matches) / sizeof(Match)) == TotalMatches;
    }

    Team* begin() { return ParticipatingTeams; }
    Team* end() { return ParticipatingTeams + NumTeamsRegistered; }
};

int InitializeTournament(Tournament* tournament);
Team CreateTeam();
bool CreateTeamPair(Team* participatingTeams, uint32_t teamSize, Match* match, uint32_t totalMatchToPlay);
bool InitializeLeaguePlay(Tournament* tournament);
bool InitializeElimination(Tournament* tournament);
bool CreateMatch(Tournament* tournament);