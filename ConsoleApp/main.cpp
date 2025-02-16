#include "Tournament.h"
#include "RNG.h"
#include <vector>

void sim_match_days(tournament* ctx)
{
	for (int i = 0; i < ctx->total_match_days; i++)
	{
		const match_day& match_day = advance_match_day(ctx);

		for (uint32_t i = 0; i < match_day.num_matchup_pairs; i++)
		{
			team_pair* pair = &match_day.matchup_pairs[i];

			bool teamAWin = gen_rand_number_normalized() > 0.5f ? true : false;

			const team_statistics* new_stat_a = register_statistics(pair->team_a, teamAWin ? modification_type::WIN : modification_type::LOSS);
			const team_statistics* new_stat_b = register_statistics(pair->team_b, teamAWin ? modification_type::LOSS : modification_type::WIN);

			std::cout << "Team " << pair->team_a->team_name << " after matchday " << match_day.match_day_number << std::endl;
			print_team_stat(new_stat_a);

			std::cout << "Team " << pair->team_b->team_name << " after matchday " << match_day.match_day_number << std::endl;
			print_team_stat(new_stat_b);
		}

		std::cout << "Press enter to move to next match day: ";
		char ch = getchar();
	}
}

int main() 
{
	std::cout << "Welcome to tournament tracker..." << std::endl;
	
	std::cout << "Enter team names" << std::endl;

	std::vector<team> team_models{};

	bool finished = false;
	while (!finished)
	{
		team team;
		std::cout << "> ";
		std::cin >> team.team_name;
		team_models.push_back(team);

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

	tournament* ctx = init_tournament(&team_models[0], team_models.size(), matchDays);

	if (ctx == nullptr)
	{
		fprintf(stderr, "Could not initialize tournament");
		return -1;
	}

	print_all_teams(ctx);
	sim_match_days(ctx);
}
