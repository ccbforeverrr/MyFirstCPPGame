#include <raylib.h>
#include "gameMain.h"

class playerData{
public:
    float X = 100;
    float Y = 100;
    float Width = 50;
    float Height = 50;
    Color c = RED;
};
playerData PlayerData{};

bool initGame(){
    return 1;
}
bool updateGame(){
    if(IsKeyDown(KEY_W)) {PlayerData.Y -= 1;}
    if(IsKeyDown(KEY_A)) {PlayerData.X -= 1;}
    if(IsKeyDown(KEY_S)) {PlayerData.Y += 1;}
    if(IsKeyDown(KEY_D)) {PlayerData.X += 1;}

    DrawRectangle(PlayerData.X, PlayerData.Y, PlayerData.Width, PlayerData.Height, PlayerData.c);

    return 1;
}
void closeGame(){

}