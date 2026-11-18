#include"gameMap.h"
#include<assert.h>
void GameMap::create(int w, int h){
    *this = {};
    mapData.resize(w * h);
    this->w = w;
    this->h = h;
    for(auto &i : mapData) {i = {};}

}

Block &GameMap::getBlockUnsafe(int x, int y){
    assert(mapData.size() == w * h);
    assert(x >= 0 && y >= 0 && x < w && y < h);
    return mapData[x+y*w];
}
Block *GameMap::getBlockSafe(int x, int y){
    assert(mapData.size() == w * h);
    if(!(x >= 0 && y >= 0 && x < w && y < h)) return nullptr;
    return &mapData[x+y*w];
}