#include<iostream>
#include<raylib.h>
#include<imgui.h>

int main(){
    InitWindow(400,500,"HOLA WORLD");
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("HI", 100, 100, 10, BLACK);
        EndDrawing();
    }
    CloseWindow();

}