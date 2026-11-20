#pragma once
#include<raylib.h>


struct AssetManager{
Texture2D dirt = {};
Texture2D textures = {};
Texture2D frame = {};
void loadAll();
};
Rectangle getTextureAtlas(int x, int y, int cellSizeX, int cellSizeY);