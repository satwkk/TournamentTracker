#include "Layer.h"

layer create_layer(const char* id, float posX, float posY, float width, float height, void (*UpdateCallback)(appcontext* ctx))
{
	layer layer = {};
	layer.id = id;
	layer.update_layer_fn = UpdateCallback;
	return layer;
}

void update_layer(appcontext* ctx, const layer& Layer)
{
	if (Layer.update_layer_fn != nullptr)
		Layer.update_layer_fn(ctx);
}

