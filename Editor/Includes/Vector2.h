#pragma once

#include "imgui/imgui.h"

struct Vector2 : ImVec2
{
	Vector2(float x, float y, float sizeX, float sizeY)
		: ImVec2(x, y) 
	{}

	Vector2(Vector2 pos, Vector2 scale)
		: Vector2(pos.x, pos.y, scale.x, scale.y)
	{}


	float SizeX = 0.f;
	float SizeY = 0.f;
};

static Vector2 GetTopLeft(const Vector2& vec)
{
	return Vector2(vec.x - (vec.SizeX / 2), vec.y - (vec.SizeY / 2), vec.SizeX, vec.SizeY);
}