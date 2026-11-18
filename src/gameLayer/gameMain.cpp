#include <raylib.h>
#include "gameMain.h"
#include <imgui.h>

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
    #pragma region secondWindow
    ImGui::Begin("PlayerSpeed");
    ImGui::Text("adjust player speed");
    ImGui::Separator();
    static float playerSpd = 1;
    ImGui::SliderFloat("slider1", &playerSpd, 1, 8);
    ImGui::End();
    #pragma endregion
    float deltaTime = GetFrameTime();
    if(deltaTime > 1.f/5){deltaTime = 1.f/5;}

    if(IsKeyDown(KEY_W) && PlayerData.Y >= 0) {PlayerData.Y -= playerSpd * 300 * deltaTime;}
    if(IsKeyDown(KEY_A) && PlayerData.X >= 0) {PlayerData.X -= playerSpd * 300 * deltaTime;}
    if(IsKeyDown(KEY_S) && PlayerData.Y <= GetScreenHeight()-PlayerData.Height) {PlayerData.Y += playerSpd * 300 * deltaTime;}
    if(IsKeyDown(KEY_D) && PlayerData.X <= GetScreenWidth()-PlayerData.Width) {PlayerData.X += playerSpd * 300 * deltaTime;}

    DrawRectangle(PlayerData.X, PlayerData.Y, PlayerData.Width, PlayerData.Height, PlayerData.c);

    return 1;
}
void closeGame(){

}