#include <iostream>
#include <stdio.h>
#include <memory>
#include <algorithm>
#include <functional>
#include <random>
#include <math.h>

#include "Tournament.h"
#include "Memory.h"

Tournament* Context = nullptr;

bool InitializeTournament(Team* Teams, uint32_t Size, uint32_t MatchDays)
{
	Context = new Tournament;
	Context->TotalMatchDays = MatchDays;
	InitializeRegisteredTeams(Teams, Size);
	return true;
}

bool InitializeRegisteredTeams(Team* Teams, uint32_t Size)
{
	Context->NumRegisteredTeams = Size;
	Context->RegisteredTeams = new Team[Size];
	MemMapCopy(Context->RegisteredTeams, Teams, Size * sizeof(Team));
	Context->Table.PlayingTeams = Context->RegisteredTeams;
	return true;
}

const MatchDay& NextMatchDay()
{
	uint32_t currentMatchDay = ++Context->CurrentMatchDay;
	std::cout << "Starting match day " << currentMatchDay << std::endl;

	// Setup math day
	uint32_t totalPairs = Context->NumRegisteredTeams / 2;
	MatchDay matchDay{};
	matchDay.MatchDayNumber = currentMatchDay;
	matchDay.MatchupPairs = new TeamPair[totalPairs];

	// Copy team pointers for shuffling
	Team** teamArrCopy = new Team*[Context->NumRegisteredTeams];
	for (uint32_t i = 0; i < Context->NumRegisteredTeams; i++)
		teamArrCopy[i] = &Context->RegisteredTeams[i];

	// Shuffle team array
	std::random_device device{};
	std::mt19937 rng(device());
	std::shuffle(teamArrCopy, teamArrCopy + Context->NumRegisteredTeams, rng);

	// Create pairs
	int currentIdx = 0;
	for (uint32_t i = 0; i + 1 < Context->NumRegisteredTeams; i += 2)
	{
		if (currentIdx >= totalPairs) break;
		TeamPair pair{};
		pair.TeamA = teamArrCopy[i];
		pair.TeamB = teamArrCopy[i + 1];
		matchDay.MatchupPairs[currentIdx++] = pair;
	}
	matchDay.NumMatchupPairs = currentIdx;
	Context->PlayedMatchDays.push_back(matchDay);
	delete[] teamArrCopy;
	return GetCurrentMatchDay();
}

const TeamStatistics* ModifyTeamStatistics(Team* Team, EModificationType Type)
{
	switch (Type)
	{
		case EModificationType::WIN:
			Team->Statistics.NumWins++;
			break;
		case EModificationType::LOSS:
			Team->Statistics.NumLoss++;
			break;
		case EModificationType::DRAW:
			Team->Statistics.NumDraw++;
			break;
	}
	return &Team->Statistics;
}

void PrintAllTeams()
{
	for (int i = 0; i < Context->NumRegisteredTeams; i++)
	{
		std::cout << Context->RegisteredTeams[i].TeamName << std::endl;
	}
}

void PrintTeamStat(const TeamStatistics* Stat)
{
	std::cout << "WinCount: " << Stat->NumWins << std::endl;
	std::cout << "LossCount: " << Stat->NumLoss<< std::endl;
	std::cout << "DrawCount: " << Stat->NumDraw << std::endl;
	std::cout << "Win Percentage: " << (float)Stat->NumWins / (Stat->NumWins + Stat->NumLoss + Stat->NumDraw) << std::endl;
}
