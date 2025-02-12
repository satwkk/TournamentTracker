#include <Windows.h>
#include <stdio.h>
#include <memory>
#include <algorithm>
#include <functional>
#include <random>
#include <math.h>

#include "Tournament.h"

Team CreateTeam()
{
    std::cout << "Enter team name: " << std::endl;
    char team_name[51];
    std::cin >> team_name;

    Team team;
    team.Name = new char[51];
    memcpy(team.Name, team_name, 51);

    return team;
}

bool CreateTeamPair(Team* participatingTeams, uint32_t teamSize, Match* match, uint32_t totalMatchToPlay)
{
    uint32_t matchIdx = 0;
    for (uint32_t i = 0; i < teamSize - 1; i++)
    {
        TeamPair pair;
        pair.TeamA = &participatingTeams[i];
        pair.TeamB = &participatingTeams[i + 1];

        if (matchIdx < totalMatchToPlay)
        {
            match[matchIdx++].Teams = pair;
            match++;
        }
    }
    return true;
}

bool InitializeLeaguePlay(Tournament* tournament)
{
    std::cout << "How many matches will each team play: " << std::endl;
    int num_matches_per_team = 0;
    std::cin >> num_matches_per_team;

    if (num_matches_per_team <= 0)
    {
        std::cerr << "Each team should at least play 1 match" << std::endl;
        return false;
    }

    tournament->TotalMatches = (tournament->NumTeamsRegistered * num_matches_per_team) / 2;
    tournament->TotalRounds = (tournament->NumTeamsRegistered * (tournament->NumTeamsRegistered - 1)) / 2;
    tournament->Matches = new Match[tournament->TotalMatches];
    Match* itr = tournament->Matches;

    for (size_t round = 0; round < tournament->TotalRounds; round++)
    {
        std::random_device rndDevice{};
        std::mt19937 rng(rndDevice());
        std::shuffle(tournament->begin(), tournament->end(), rng);
        CreateTeamPair(tournament->ParticipatingTeams, tournament->NumTeamsRegistered, itr, tournament->TotalMatches);
    }
    return true;
}

bool InitializeElimination(Tournament* tournament)
{
    return false;
}

bool CreateMatch(Tournament* tournament)
{
    switch (tournament->Type)
    {
    case TournamentType::LeaguePlay: return InitializeLeaguePlay(tournament);
    case TournamentType::Elimination: return InitializeElimination(tournament);
    default: return false;
    }
}

int InitializeTournament(Tournament* tournament)
{
    // Initialize state of tournament
    std::cout << "How many teams you want to initialize..." << std::endl;
    uint32_t num_teams = 0;
    std::cin >> num_teams;

    if (num_teams <= 0 || num_teams >= MAXTEAMS)
    {
        std::cerr << "Cannot create tournament with 0 or more than " << MAXTEAMS << " teams..." << std::endl;
        return TOURNAMENTFAILED;
    }

    tournament->NumTeamsRegistered = 0;
    std::cout << "Team creation menu...." << std::endl;
    while (tournament->NumTeamsRegistered < num_teams)
    {
        tournament->ParticipatingTeams[tournament->NumTeamsRegistered++] = CreateTeam();
    }

    std::cout << "What kind of tournament you want to play" << std::endl;
    std::cout << "1. League Play" << std::endl;
    std::cout << "2. Elimination" << std::endl;
    std::cout << "> ";

    int tournamentType = -1;
    std::cin >> tournamentType;

    if (tournamentType < 1 || tournamentType > 2)
    {
        std::cerr << "No tournament type found" << std::endl;
        return TOURNAMENTFAILED;
    }

    tournament->Type = static_cast<TournamentType>(tournamentType);

    if (!CreateMatch(tournament))
    {
        std::cerr << "Could not initialize matches for tournament" << std::endl;
        return TOURNAMENTFAILED;
    }

    tournament->IsInitialized = true;
    return TOURNAMENTSUCCESS;
}