#include "Tournament.h"
#include "RNG.h"
#include <vector>

void SimulateMatchDays()
{
	for (int i = 0; i < Context->TotalMatchDays; i++)
	{
		const MatchDay& matchDay = NextMatchDay();

		for (uint32_t i = 0; i < matchDay.NumMatchupPairs; i++)
		{
			TeamPair* pair = &matchDay.MatchupPairs[i];

			bool teamAWin = GenerateRandomNumberNormalized() > 0.5f ? true : false;

			const TeamStatistics* newTeamAStats = ModifyTeamStatistics(pair->TeamA, teamAWin ? EModificationType::WIN : EModificationType::LOSS);
			const TeamStatistics* newTeamBStats = ModifyTeamStatistics(pair->TeamB, teamAWin ? EModificationType::LOSS : EModificationType::WIN);

			std::cout << "Team " << pair->TeamA->TeamName << " after matchday " << matchDay.MatchDayNumber << std::endl;
			PrintTeamStat(newTeamAStats);

			std::cout << "Team " << pair->TeamB->TeamName << " after matchday " << matchDay.MatchDayNumber << std::endl;
			PrintTeamStat(newTeamBStats);
		}

		std::cout << "Press enter to move to next match day: ";
		char ch = getchar();
	}
}

int main() 
{
	std::cout << "Welcome to tournament tracker..." << std::endl;
	
	std::cout << "Enter team names" << std::endl;

	std::vector<Team> teamModels{};

	bool finished = false;
	while (!finished)
	{
		Team team;
		std::cout << "> ";
		std::cin >> team.TeamName;
		teamModels.push_back(team);

		std::cout << "Do you wish to continue(y, n): ";
		char ch;
		std::cin >> ch;
		switch (ch)
		{
			case 'y':
			{
				finished = false;
				break;
			}
			case 'n':
			{
				finished = true;
				break;
			}
			default:
			{
				finished = false;
				break;
			}
		}
	}

	uint32_t matchDays = 0;
	std::cout << "Enter total number of match days to play: ";
	std::cin >> matchDays;

	if (!InitializeTournament(&teamModels[0], teamModels.size(), matchDays))
	{
		fprintf(stderr, "Could not initialize tournament");
		return -1;
	}

	PrintAllTeams();

	SimulateMatchDays();
}
