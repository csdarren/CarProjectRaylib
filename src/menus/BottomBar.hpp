#pragma once
#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP

#include "rlImGui.h"
#include <iostream>

#include "../gui.hpp"

class BottomBar : private Gui {
  private:
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImVec2 *pScreenSize;

    static constexpr ImVec2 BURGER_BUTTON_SIZE = {40.0F, 40.0F};
    static constexpr float BURGER_WIDTH_DIVISOR = 0.20;
    static constexpr int HEIGHT_DIVISOR = 5;
    static constexpr int MAX_UI_TEXTURES = 10;

    Texture burgerTex{};

    ImVec2 size;
    ImVec2 pos;
    ImVec2 burgerBtnPos;

  public:
    BottomBar()
        : pScreenSize(&getScreenSize()) {
        this->size = {pScreenSize->x, pScreenSize->y / HEIGHT_DIVISOR};
        this->pos = {0, pScreenSize->y - size.y};
        this->burgerBtnPos = {(size.x * BURGER_WIDTH_DIVISOR) - (BURGER_BUTTON_SIZE.x / 2), (size.y / 2) - (BURGER_BUTTON_SIZE.y / 2)};
        this->burgerTex = LoadTexture("../assets/images/Hamburger.png");
    }
    auto getPos() -> ImVec2 {
        return this->pos;
    }
    auto getSize() -> ImVec2 {
        return this->size;
    }
    auto getBurgerBtnPos() -> ImVec2 {
        return this->burgerBtnPos;
    }
    void Render() {
        if (getBottomBarState()) {
            ImGui::SetNextWindowPos(pos, 1);
            ImGui::SetNextWindowSize(size, 1);
            ImGui::Begin("Main Screen", nullptr, flags);

            if (rlImGuiImageButton("Hamburger", &burgerTex)) {
                // put what happens when button pressed here:
                std::cout << "Inverting BurgerState" << "\n";
                setBurgerState(!getBurgerState()); // toggles burger state to the opposite of what it is
                std::cout << "Current BurgerState = " << getBurgerState() << "\n";
            }
            ImGui::End();
        }
    }
};

#endif
