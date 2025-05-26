#pragma once
#ifndef GUI_HPP
#define GUI_HPP
#include <iostream>
#include <array>

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

class Gui {
  private:
    ImVec2 screenSize;

  public:
    Gui() : screenSize{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())} {
        ImGui::CreateContext();
        ImGuiIO &GuiIO = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(1, 0, 0, 0);          // Button inactive (Unfocused / not hovering)
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1, 0, 0, 0);   // Button hovered (Focused)
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(1, 0, 0, 0);    // Button active (Focused, clicked)
    }
    auto getScreenSize() -> ImVec2 {
        return screenSize;
    }
};

class BottomBar : private Gui {
  private:
    ImGuiWindowFlags bottomBarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImVec2 ScreenSize;

    static constexpr ImVec2 BURGER_BUTTON_SIZE = {40.0F, 40.0F};
    static constexpr float WIDTH_DIVISOR = 0.20;
    static constexpr int HEIGHT_DIVISOR = 5;
    static constexpr int MAX_UI_TEXTURES = 10;

    Texture burgerTex{};
    std::array<Texture, MAX_UI_TEXTURES> UITextures{};

    ImVec2 bottomBarSize;
    ImVec2 bottomBarPos;
    ImVec2 buttonSize;
    ImVec2 burgerButtonPos;

  public:
    BottomBar() : buttonSize(BURGER_BUTTON_SIZE) {
        this->ScreenSize = getScreenSize();
        std::cout << "screensize x: " << ScreenSize.x << " screensize.y: " << ScreenSize.y << "\n";
        this->bottomBarSize = {ScreenSize.x, ScreenSize.y / HEIGHT_DIVISOR};
        this->bottomBarPos = {0, ScreenSize.y - bottomBarSize.y};
        std::cout << "screensize x: " << bottomBarPos.x << " screensize.y: " << bottomBarPos.y << "\n";
        this->burgerButtonPos = {(bottomBarSize.x * WIDTH_DIVISOR) - (buttonSize.x / 2), (bottomBarSize.y / 2) - (buttonSize.y / 2)};
        this->burgerTex = LoadTexture("../assets/images/Hamburger.png");
        this->UITextures = {burgerTex};
    }
    auto getPos() -> ImVec2 {
        return bottomBarPos;
    }
    auto getSize() -> ImVec2 {
        return bottomBarSize;
    }
    auto getBurgerBtnPos() -> ImVec2 {
        return burgerButtonPos;
    }
    void Render() const {
        ImGui::SetNextWindowPos(bottomBarPos, 1);
        ImGui::SetNextWindowSize(bottomBarSize, 1);
        ImGui::Begin("Main Screen", nullptr, bottomBarFlags);

        if (rlImGuiImageButton("Hamburger", &burgerTex)) {
            // put what happens when button pressed here:
            std::cout << "Button pressed" << "\n";
        }

        ImGui::End();
    }
};

#endif
