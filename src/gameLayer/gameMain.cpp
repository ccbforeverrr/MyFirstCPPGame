#include <raylib.h>
#include "gameMain.h"
#include <imgui.h>
#include "assetManager.h"
#include "gameMap.h"


#define UNIT 16.0f

class GanmeData{
public:
    GameMap gameMap;
    Camera2D camera;
}gameData;
class PlayerData{
public:
    float X = 0;
    float Y = 0;
    float Width = UNIT;
    float Height = UNIT;
    Color c = RED;
};
PlayerData playerData{};
AssetManager assetManager;

bool initGame(){
    assetManager.loadAll();

    gameData.gameMap.create(30,10);

    gameData.gameMap.getBlockUnsafe(0,6).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1,6).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(2,6).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(3,7).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(4,8).type = Block::dirt;

    gameData.camera.target = {0,0};
    gameData.camera.rotation = 0.0f;
    gameData.camera.zoom = 2.0f;


    return 1;
}

void renderMap(){
    for(int y = 0; y < gameData.gameMap.h; y++){
        for(int x = 0; x < gameData.gameMap.w; x++){
            auto &tempBlock = gameData.gameMap.getBlockUnsafe(x,y);
            if(tempBlock.type != Block::air){
                float size = UNIT;
                float posX = x * size;
                float posY = y * size;
                DrawTexturePro(
                    assetManager.dirt,
                    {0,0,(float)assetManager.dirt.width, (float)assetManager.dirt.height},  //source
                    {posX, posY, size, size},                                               //position
                    {0,0},                                                                  //origin
                    0,                                                                      //rotation
                    WHITE                                                                   //tint
                );

            }
        }
    }
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
    gameData.camera.offset = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    
    if(deltaTime > 1.f/50){deltaTime = 1.f/50;}
    #pragma region playerControl
    if(IsKeyDown(KEY_W) && playerData.Y >= 0) {playerData.Y -= playerSpd * 200 * deltaTime;}
    if(IsKeyDown(KEY_A) && playerData.X >= 0) {playerData.X -= playerSpd * 200 * deltaTime;}
    if(IsKeyDown(KEY_S) && playerData.Y <= GetScreenHeight()-playerData.Height) {playerData.Y += playerSpd * 200 * deltaTime;}
    if(IsKeyDown(KEY_D) && playerData.X <= GetScreenWidth()-playerData.Width) {playerData.X += playerSpd * 200 * deltaTime;}
    #pragma endregion
    #pragma region cameraControl
    if(IsKeyDown(KEY_UP)) gameData.camera.target.y -= 200.f * deltaTime;
    if(IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 200.f * deltaTime;
    if(IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 200.f * deltaTime;
    if(IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 200.f * deltaTime;
    #pragma endregion
    BeginMode2D(gameData.camera);
    renderMap();

    DrawRectangle(playerData.X, playerData.Y, playerData.Width, playerData.Height, playerData.c);
    EndMode2D();
    return 1;
}
void closeGame(){

}