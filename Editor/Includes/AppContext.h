#pragma once

struct window;
struct team;
struct tournament;

struct appcontext
{
	window* main_window_handle;
	tournament* tournament_ref;
};
