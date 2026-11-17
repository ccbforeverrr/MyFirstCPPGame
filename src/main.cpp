#include<iostream>
#include<raylib.h>
#include<imgui.h>
#include<rlImGui.h>




int main(){
    InitWindow(400,500,"HOLA WORLD");

    rlImGuiSetup(true);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);

            rlImGuiBegin();

            DrawText("HI", 100, 100, 10, BLACK);

            ImGui::Begin("test");
            ImGui::Text("HELLO");
            ImGui::Button("button");
            ImGui::End();

            rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

}