#pragma once
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../gui.hpp"

class Debug : private Gui {
  private:
    ImGuiWindowFlags flags;
    int speed{0};

  public:
    auto Render() {
        if (getDebugMenuState()) {
            ImGui::SetNextWindowPos(ImVec2{100, 100}, 1);
            ImGui::SetNextWindowSize(ImVec2{400, 400}, 1);
            ImGui::Begin("Debug Menu", nullptr, flags);
            ImGui::SliderInt("Speed", &speed, 0, 120);
            ImGui::End();
        }
    }
    [[nodiscard]] auto getSpeed() const -> int {
        return speed;
    }
};

#endif
