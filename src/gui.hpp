#pragma once
#ifndef GUI_HPP
#define GUI_HPP

#include "imGuiUtil.hpp"

class Gui {
  private:
    ImVec2 screenSize;
    ImGuiWindowFlags bottomBarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImVec2 bottomBarSize = {screenSize.x, screenSize.y / 5};
    ImVec2 bottomBarPos = {0, static_cast<float>(screenSize.y * 0.80)};
    ImVec2 buttonSize = {40.0f, 40.0f};
    ImVec2 buttonPos = ImVec2{bottomBarSize.x / 20 - (buttonSize.x / 2), bottomBarSize.y / 2 - (buttonSize.y / 2)};

  public:
    Gui()
        : screenSize{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())} {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(1, 0, 0, 0);        // Button inactive (Unfocused / not hovering)
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1, 0, 0, 0); // Button hovered (Focused)
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(1, 0, 0, 0);  // Button active (Focused, clicked)
    }
    ~Gui() {};
    void BottomBarWindow(const Texture &texture) {
        ImGui::Begin("Main Screen", NULL, bottomBarFlags);
        if (rlImGuiImageButton("Hamburger", &texture)) {
        }
        ImGui::End();
    }
    ImVec2 GetBottomBarPos() {
        return bottomBarPos;
    }
    ImVec2 GetBottomBarSize() {
        return bottomBarSize;
    }
    ImVec2 GetBottomBarButtonPos() {
        return buttonPos;
    }
};

#endif