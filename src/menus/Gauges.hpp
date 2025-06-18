#pragma once
#ifndef GAUGES_HPP
#define GAUGES_HPP

#include "imgui.h"
#include "rlImGui.h"
#include <iostream>
#include "../gui.hpp"

class Gauges : private Gui {
  private:
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground;
    static constexpr int STATUS_BAR_HEIGHT_DIVISOR = 30;
    static constexpr int HEIGHT_SIZE_DIVISOR = 10;
    static constexpr int HEIGHT_POS_OFFSET = 10;
    static constexpr int WIDTH_SIZE_OFFSET = 100;
    static constexpr int WIDTH_POS_OFFSET = 50;
    ImVec2 *pScreenSize;
    ImVec2 speedoSize;
    ImVec2 speedoPos;

  public:
    Gauges()
        : pScreenSize(&getScreenSize()) {
        this->speedoSize = {pScreenSize->x - WIDTH_SIZE_OFFSET, (pScreenSize->y / HEIGHT_SIZE_DIVISOR)};
        this->speedoPos = {WIDTH_POS_OFFSET, (pScreenSize->y / STATUS_BAR_HEIGHT_DIVISOR) + HEIGHT_POS_OFFSET};
    }
    auto Render() {
        if (getGaugesState()) {
            ImGui::SetNextWindowPos(speedoPos, 1);
            ImGui::SetNextWindowSize(speedoSize, 1);

            ImGui::Begin("Gauge Menu", nullptr, flags);

            ImGui::PushFont(Gui::getFont(1));

            const char *SPEEDOMETER_NUMBERS = "0        10        20        30        40        50        60        70        80        90        100       110       120";

            ImVec2 textSize = ImGui::CalcTextSize(SPEEDOMETER_NUMBERS);
            float textPosX = (speedoSize.x - textSize.x) * 0.5F;
            float textPosY = (speedoSize.y - textSize.y) * 0.5F;
            ImGui::SetCursorPosX(textPosX);
            ImGui::SetCursorPosY(textPosY);

            ImGui::Text("%s", SPEEDOMETER_NUMBERS);
            ImGui::PopFont();

            ImGui::End();
        }
    }
    auto getSpeedoSize() -> ImVec2 {
        return speedoSize;
    }
    auto getSpeedoPos() -> ImVec2 {
        return speedoPos;
    }
};

#endif
