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

    gameData.gameMap.create(300,300);

    #pragma region map
    for(int i = 0; i < 300; i++){
        for(int j = 0; j < 300; j++){
            gameData.gameMap.getBlockUnsafe(i,j).type = Block::stone;
        }
    }
    gameData.gameMap.getBlockUnsafe(0,6).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1,6).type = Block::goldBlock;
    gameData.gameMap.getBlockUnsafe(2,6).type = Block::ironBlock;
    gameData.gameMap.getBlockUnsafe(3,7).type = Block::grass;
    gameData.gameMap.getBlockUnsafe(4,8).type = Block::sandStone;
    #pragma endregion

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
                    assetManager.textures,
                    getTextureAtlas(tempBlock.type, 0, 32, 32),                             //source
                    {posX, posY, size, size},                                               //position
                    {0,0},                                                                  //origin
                    0,                                                                      //rotation
                    WHITE                                                                   //tint
                );
            }
        }
    }
}
void renderMapOpt(){
    Vector2 topLeft = GetScreenToWorld2D({0,0}, gameData.camera);
    Vector2 bottomRight = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);
    int startXView = (int)(topLeft.x/UNIT-1);
    int startYView = (int)(topLeft.y/UNIT-1);
    int endXView = (int)(bottomRight.x/UNIT+1);
    int endYView = (int)(bottomRight.y/UNIT+1);

    startXView = std::clamp(startXView, 0, gameData.gameMap.w - 1);
    startYView = std::clamp(startYView, 0, gameData.gameMap.h - 1);
    endXView = std::clamp(endXView, 0, gameData.gameMap.w - 1);
    endYView = std::clamp(endYView, 0, gameData.gameMap.h - 1);

    for(int y = startYView; y < endYView; y++){
        for(int x = startXView; x < endXView; x++){
            auto &tempBlock = gameData.gameMap.getBlockUnsafe(x,y);
            if(tempBlock.type != Block::air){
                float size = UNIT;
                float posX = x * size;
                float posY = y * size;
                DrawTexturePro(
                    assetManager.textures,
                    getTextureAtlas(tempBlock.type, 0, 32, 32),                             //source
                    {posX, posY, size, size},                                               //position
                    {0,0},                                                                  //origin
                    0,                                                                      //rotation
                    WHITE                                                                   //tint
                );
            }
        }
    }
}
void showCursorBlock(){
    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX = (int)floor(worldPos.x/UNIT);
    int blockY = (int)floor(worldPos.y/UNIT);
    DrawTexturePro(
        assetManager.frame,
        getTextureAtlas(0,0,32,32),
        {(float)blockX * UNIT, (float)blockY * UNIT, UNIT, UNIT},
        {0,0},
        0,
        WHITE
    );
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){                                       //break blocks
        auto tempBlock = gameData.gameMap.getBlockSafe(blockX, blockY);
        if(tempBlock){
            *tempBlock = {};
        }
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        auto tempBlock = gameData.gameMap.getBlockSafe(blockX, blockY);
        if(tempBlock && tempBlock->type == Block::air){
            tempBlock->type = Block::clay;
        }
    }

}
bool updateGame(){
    DrawFPS(10,10);
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
    // #pragma region cameraControl
    // if(IsKeyDown(KEY_UP)) gameData.camera.target.y -= 200.f * deltaTime;
    // if(IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 200.f * deltaTime;
    // if(IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 200.f * deltaTime;
    // if(IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 200.f * deltaTime;
    // #pragma endregion
    gameData.camera.target.x = playerData.X;            //camera following player
    gameData.camera.target.y = playerData.Y;
    BeginMode2D(gameData.camera);
    renderMapOpt();
    showCursorBlock();


    DrawRectangle(playerData.X, playerData.Y, playerData.Width, playerData.Height, playerData.c);
    EndMode2D();
    return 1;
}
void closeGame(){

}