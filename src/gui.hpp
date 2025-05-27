#pragma once
#ifndef GUI_HPP
#define GUI_HPP
#include <iostream>
#include <ctime>

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

class Gui {
  private:
    // INFO: Could cause issues when resizing, maybe add a screenSize update function in loop that gets new screenSize every frame
    inline static ImVec2 ScreenSize;
    inline static bool showBurgerMenu{false};
    inline static bool showBottomBar{true}; // defaults to true, if you need to toggle the bottom bar, this is how you do it. set to false
    inline static bool showStatusBar{true}; // defaults to true, if you need to toggle the bottom bar, this is how you do it. set to false

  public:
    Gui() {
        Gui::ScreenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
        ImGui::CreateContext();
        ImGuiIO &GuiIO = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(1, 0, 0, 0);        // Button inactive (Unfocused / not hovering)
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1, 0, 0, 0); // Button hovered (Focused)
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(1, 0, 0, 0);  // Button active (Focused, clicked)
        std::cout << "ScreenSize X: " << ScreenSize.x << "\n";
        std::cout << "ScreenSize Y: " << ScreenSize.y << "\n";
    }
    static auto getScreenSize() -> ImVec2 & {
        return ScreenSize;
    }
    [[nodiscard]] static auto getBurgerState() -> bool {
        return Gui::showBurgerMenu;
    }
    static auto setBurgerState(bool state) -> void {
        Gui::showBurgerMenu = state;
    }

    [[nodiscard]] static auto getBottomBarState() -> bool {
        return Gui::showBottomBar;
    }
    static auto setBottomBarState(bool state) -> void {
        Gui::showBottomBar = state;
    }

    [[nodiscard]] static auto getStatusBarState() -> bool {
        return Gui::showStatusBar;
    }
    static auto setStatusBarState(bool state) -> void {
        Gui::showStatusBar = state;
    }
};

class StatusBar : Gui {
  private:
    static constexpr int HEIGHT_DIVISOR = 30;
    static constexpr int RIGHT_BAR_OFFSET = 10;
    ImVec2 *pScreenSize;
    ImVec2 barSize;
    ImVec2 barPos;
    ImGuiWindowFlags barFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
    const char *time{"Test time"};

  public:
    StatusBar()
        : pScreenSize(&getScreenSize()) {
        this->barSize = {pScreenSize->x, pScreenSize->y / HEIGHT_DIVISOR};
        this->barPos = {0, 0};
    }
    auto Render() {
        if (getStatusBarState()) {
            ImGui::SetNextWindowPos(barPos, 1);
            ImGui::SetNextWindowSize(barSize, 1);
            ImGui::Begin("Status Bar", nullptr, barFlags);
            ImVec2 textSize = ImGui::CalcTextSize(time);

            ImGui::SetCursorPosX(barSize.x - textSize.x - RIGHT_BAR_OFFSET);
            ImGui::Text(time);

            ImGui::End();
        }
    }
};

class BurgerMenu : Gui {
  private:
    ImVec2 *pScreenSize;
    static constexpr int WIDTH_DIVISOR = 5;
    static constexpr ImVec2 CLOSE_BUTTON_OFFSET{10, 10};
    static constexpr ImVec2 CLOSE_BUTTON_SIZE{50, 50};
    static constexpr ImGuiWindowFlags menuFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImVec2 menuSize;
    ImVec2 menuPos;

    ImVec2 closeBtnPos;

  public:
    BurgerMenu()
        : pScreenSize(&getScreenSize()) {
        this->menuSize = {pScreenSize->x / WIDTH_DIVISOR, pScreenSize->y};
        this->menuPos = {0, 0};

        this->closeBtnPos = {pScreenSize->x - CLOSE_BUTTON_OFFSET.x, pScreenSize->y - CLOSE_BUTTON_OFFSET.y};
    }
    void Render() {
        if (getBurgerState()) {
            ImGui::SetNextWindowPos(menuPos, 1);
            ImGui::SetNextWindowSize(menuSize, 1);
            ImGui::Begin("Burger Menu", nullptr, menuFlags);

            ImGui::SetCursorPosX(menuSize.x - CLOSE_BUTTON_SIZE.x - CLOSE_BUTTON_OFFSET.x);
            if (ImGui::Button("Close Button")) {
            }

            ImGui::End();
        }
    }
};

class BottomBar : private Gui {
  private:
    ImGuiWindowFlags barFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImVec2 *pScreenSize;

    static constexpr ImVec2 BURGER_BUTTON_SIZE = {40.0F, 40.0F};
    static constexpr float BURGER_WIDTH_DIVISOR = 0.20;
    static constexpr int HEIGHT_DIVISOR = 5;
    static constexpr int MAX_UI_TEXTURES = 10;

    Texture burgerTex{};

    ImVec2 barSize;
    ImVec2 barPos;
    ImVec2 burgerBtnPos;

  public:
    BottomBar()
        : pScreenSize(&getScreenSize()) {
        this->barSize = {pScreenSize->x, pScreenSize->y / HEIGHT_DIVISOR};
        this->barPos = {0, pScreenSize->y - barSize.y};
        this->burgerBtnPos = {(barSize.x * BURGER_WIDTH_DIVISOR) - (BURGER_BUTTON_SIZE.x / 2), (barSize.y / 2) - (BURGER_BUTTON_SIZE.y / 2)};
        this->burgerTex = LoadTexture("../assets/images/Hamburger.png");
    }
    auto getPos() -> ImVec2 {
        return this->barPos;
    }
    auto getSize() -> ImVec2 {
        return this->barSize;
    }
    auto getBurgerBtnPos() -> ImVec2 {
        return this->burgerBtnPos;
    }
    void Render() {
        if (getBottomBarState()) {
            ImGui::SetNextWindowPos(barPos, 1);
            ImGui::SetNextWindowSize(barSize, 1);
            ImGui::Begin("Main Screen", nullptr, barFlags);

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
