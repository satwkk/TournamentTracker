#pragma once

#include <random>

float gen_rand_number_normalized()
{
	return (float)rand() / RAND_MAX;
}

float gen_rand_number_range(float min, float max, bool normalize = false)
{
	std::random_device device;
	std::mt19937 rng(device());
	float randomNumber = std::uniform_int_distribution<std::mt19937::result_type>(min, max)(rng);
	return normalize ? (randomNumber / max) : randomNumber;
}