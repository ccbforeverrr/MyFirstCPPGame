#include<iostream>
#include<raylib.h>
#include<imgui.h>
#include<rlImGui.h>
#include<gameMain.h>


int main(){
    InitWindow(960,864,"HOLA WORLD");
    rlImGuiSetup(true);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    SetExitKey(KEY_NULL);           //disable esc from closing the window
    SetTargetFPS(60);

    if(!initGame()){
        return 0;
    }

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);

            rlImGuiBegin();

            #pragma region docking
            //docking
            ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
            ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
            ImGui::PopStyleColor(2);
            #pragma endregion

            #pragma region firstWindow
            ImGui::Begin("test1");
            ImGui::Text("HELLO");
            ImGui::Button("button1");
            if(ImGui::Button("button2")){
                std::cout<<"hi"<<std::endl;
            }
            ImGui::End();
            #pragma endregion

            if(!updateGame()){
                CloseWindow();
            }
            rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    closeGame();
}