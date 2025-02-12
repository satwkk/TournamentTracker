#pragma once

struct Window;

struct Layer
{
	const char* Id;
	void (*UpdateLayerCallback)(const Window& Handle);
};

Layer CreateLayer(const char* id, float posX, float posY, float width, float height, void (*UpdateCallback)(const Window& Handle));
void UpdateLayer(const Window& Handle, const Layer& Layer);