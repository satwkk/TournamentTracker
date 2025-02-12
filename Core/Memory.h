#pragma once

#include <cstdint>

template<typename TDest, typename TSrc>
void MemMapCopy(TDest* destination, TSrc* src, uint32_t srcSizeBytes)
{
	if (src == nullptr)
	{
		std::cerr << "Src is null..." << std::endl;
		return;
	}

	if (destination == nullptr)
	{
		std::cerr << "Destination pointer is null..." << std::endl;
		return;
	}

	if (sizeof(TDest) != sizeof(TSrc))
	{
		fprintf(stderr, "Src and Destination are not of same size...");
		return;
	}
	std::memcpy(destination, src, srcSizeBytes);
}
