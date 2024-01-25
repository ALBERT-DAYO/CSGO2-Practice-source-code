#pragma once
#include "overlay.h"


void Overlay::m_Menu()

{
    ImGui::SetNextWindowSize({ 700, 700 }, 0);

    ImGui::Begin("##NULL", (bool*)NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    ImGui::BeginChild("##SelectMenu", ImVec2(700.f, 60.f));

    static int menu = 0;

    if (ImGui::Button("Aim", ImVec2(230.f, 50.f)))
        menu = 0;
    ImGui::SameLine();
    if (ImGui::Button("ESP", ImVec2(230.f, 50.f)))
        menu = 1;
    ImGui::SameLine();
    if (ImGui::Button("Misc", ImVec2(230.f, 50.f)))
        menu = 2;

    ImGui::EndChild();


    ImGui::BeginChild("##MainMenu", ImVec2(700.f, 700.f));


    ImGui::NewLine();


    switch (menu)
    {
    case 0:
        ImGui::Text("AIM");
        ImGui::Separator();

        break;
    case 1:
        ImGui::Text("ESP");
        ImGui::Separator();

        break;
    case 2:
        ImGui::Text("Misc");
        ImGui::Separator();

       
        break;

    default:
        break;
    }

    ImGui::EndChild();

    ImGui::End();
}
