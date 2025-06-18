#pragma once
#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <ctime>
#include <string>
#include "../gui.hpp"

class StatusBar : Gui {
  private:
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
    static constexpr int HEIGHT_DIVISOR = 30;
    static constexpr int RIGHT_BAR_OFFSET = 10;
    ImVec2 *pScreenSize;
    ImVec2 size;
    ImVec2 pos;

  public:
    StatusBar()
        : pScreenSize(&getScreenSize()) {
        this->size = {pScreenSize->x, pScreenSize->y / HEIGHT_DIVISOR};
        this->pos = {0, 0};
    }
    auto Render() {
        if (getStatusBarState()) {
            ImGui::SetNextWindowPos(pos, 1);
            ImGui::SetNextWindowSize(size, 1);
            ImGui::Begin("Status Bar", nullptr, flags);
            time_t cte = time(nullptr);
            std::string currentTime = ctime(&cte);
            ImVec2 textSize = ImGui::CalcTextSize(currentTime.c_str());

            ImGui::SetCursorPosX(size.x - textSize.x - RIGHT_BAR_OFFSET);
            ImGui::Text("%s", currentTime.c_str());

            ImGui::End();
        }
    }
};

#endif
