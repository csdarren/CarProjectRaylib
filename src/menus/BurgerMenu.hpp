#pragma once
#ifndef BURGERMENU_HPP
#define BURGERMENU_HPP

#include "../gui.hpp"

class BurgerMenu : Gui {
  private:
    ImVec2 *pScreenSize;
    static constexpr int WIDTH_DIVISOR = 5;
    static constexpr ImVec2 CLOSE_BUTTON_OFFSET{10, 10};
    static constexpr ImVec2 CLOSE_BUTTON_SIZE{50, 50};
    static constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImVec2 size;
    ImVec2 pos;

    ImVec2 closeBtnPos;

  public:
    BurgerMenu()
        : pScreenSize(&getScreenSize()) {
        this->size = {pScreenSize->x / WIDTH_DIVISOR, pScreenSize->y};
        this->pos = {0, 0};

        this->closeBtnPos = {pScreenSize->x - CLOSE_BUTTON_OFFSET.x, pScreenSize->y - CLOSE_BUTTON_OFFSET.y};
    }
    void Render() {
        if (getBurgerState()) {
            ImGui::SetNextWindowPos(pos, 1);
            ImGui::SetNextWindowSize(size, 1);
            ImGui::Begin("Burger Menu", nullptr, flags);

            ImGui::SetCursorPosX(size.x - CLOSE_BUTTON_SIZE.x - CLOSE_BUTTON_OFFSET.x);
            if (ImGui::Button("Close", CLOSE_BUTTON_SIZE)) {
                setBurgerState(!getBurgerState());
            }

            ImGui::End();
        }
    }
};

#endif
