#pragma once

struct Window;
struct Team;

struct AppContext
{
	Window* MainWindowHandle;
	std::vector<Team> RegisteredTeams;
};
