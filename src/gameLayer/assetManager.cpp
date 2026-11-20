#include"assetManager.h"
void AssetManager::loadAll(){
    dirt = LoadTexture(RESOURCES_PATH "dirt.png");
    textures = LoadTexture(RESOURCES_PATH "textures.png");
    frame = LoadTexture(RESOURCES_PATH "frame.png");
}
Rectangle getTextureAtlas(int x, int y, int cellSizeX, int cellSizeY){
    return Rectangle{(float)x * cellSizeX, (float)y * cellSizeY, (float)cellSizeX, (float)cellSizeY};
}