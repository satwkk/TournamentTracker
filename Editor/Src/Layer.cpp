#include "Layer.h"

Layer CreateLayer(const char* id, float posX, float posY, float width, float height, void (*UpdateCallback)(const Window& Handle))
{
	Layer layer = {};
	layer.Id = id;
	layer.UpdateLayerCallback = UpdateCallback;
	return layer;
}

void UpdateLayer(const Window& Handle, const Layer& Layer)
{
	if (Layer.UpdateLayerCallback != nullptr)
		Layer.UpdateLayerCallback(Handle);
}

