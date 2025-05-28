#pragma once
#ifndef GUI_HPP
#define GUI_HPP

#include "imgui.h"
#include "raylib.h"

// INFO: Check individual files for each imgui menu that is rendered. These can be found in ./menus/
// INFO: This class is only made to help manage all windows visibility from one location, and also set standards for all windows

class Gui {
  private:
    // INFO: Could cause issues when resizing, maybe add a screenSize update function in loop that gets new screenSize every frame
    inline static ImVec2 ScreenSize;
    inline static bool showBurgerMenu{false};
    inline static bool showBottomBar{true}; // defaults to true, if you need to toggle the bottom bar, this is how you do it. set to false
    inline static bool showStatusBar{true}; // defaults to true, if you need to toggle the status bar, this is how you do it. set to false

  public:
    Gui() {
        Gui::ScreenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
        ImGui::CreateContext();
        ImGuiIO &GuiIO = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(1, 0, 0, 0);        // Button inactive (Unfocused / not hovering)
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1, 0, 0, 0); // Button hovered (Focused)
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(1, 0, 0, 0);  // Button active (Focused, clicked)
    }
    static auto getScreenSize() -> ImVec2 & {
        return ScreenSize;
    }

    // METHODS for BurgerMenu
    [[nodiscard]] static auto getBurgerState() -> bool {
        return Gui::showBurgerMenu;
    }
    static auto setBurgerState(bool state) -> void {
        Gui::showBurgerMenu = state;
    }

    // METHODS for BottomBar
    [[nodiscard]] static auto getBottomBarState() -> bool {
        return Gui::showBottomBar;
    }
    static auto setBottomBarState(bool state) -> void {
        Gui::showBottomBar = state;
    }

    // METHODS FOR StatusBar
    [[nodiscard]] static auto getStatusBarState() -> bool {
        return Gui::showStatusBar;
    }
    static auto setStatusBarState(bool state) -> void {
        Gui::showStatusBar = state;
    }
};
#endif
