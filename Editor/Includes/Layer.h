#pragma once

#include "AppContext.h"

struct window;

struct layer
{
	const char* id;
	void (*update_layer_fn)(appcontext* ctx);
};

layer create_layer(const char* id, float posX, float posY, float width, float height, void (*UpdateCallback)(appcontext* ctx));
void update_layer(appcontext* ctx, const layer& layer);