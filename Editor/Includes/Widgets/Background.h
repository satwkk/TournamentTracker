#pragma once

#include "Widgets/Widget.h"

class Background : IWidget
{
public:
	Background() = default;
	Background(const Window& handle, const std::string& id);
	virtual ~Background();
	void Update() override;
};