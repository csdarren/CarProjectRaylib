#ifndef DRAW_HPP
#define DRAW_HPP

#include "imgui.h"
#include "raylib.h"
#include "raymath.h"
class Draw {
  private:
    Model carModel{};
    bool drawCar{false};
    bool drawFloor{true};
    bool drawSpeedo{true};

    static constexpr Vector3 CAR_POS = {0.0F, 0.0F, 0.0F};
    static constexpr Vector2 FLOOR_SIZE{1000.0, 1000.0};

  public:
    Draw() {
        this->carModel = LoadModel("../assets/models/MiniCooper.glb");
    }

    Draw(const Draw &) = default;
    Draw(Draw &&) = delete;
    auto operator=(const Draw &) -> Draw & = default;
    auto operator=(Draw &&) -> Draw & = delete;

    ~Draw() {
        UnloadModel(carModel);
    }

    // Toggles the drawing of different elements
    auto toggleCarState() -> void {
        this->drawCar = !this->drawCar;
    }
    auto toggleFloorState() -> void {
        this->drawFloor = !this->drawFloor;
    }
    auto toggleSpeedoState() -> void {
        this->drawSpeedo = !this->drawSpeedo;
    }

    auto Floor() const -> void {
        if (drawFloor) {
            DrawPlane(Vector3Zero(), FLOOR_SIZE, GRAY);
        }
    }

    auto Car() -> void {
        if (drawCar) {
            for (int i = 0; i < carModel.materialCount; i++) {
                DrawModel(carModel, CAR_POS, 1.0F, WHITE);
            }
        }
    }
    auto Speedometer(ImVec2 pos, ImVec2 size, int speed) const -> void {
        if (drawSpeedo) {
            int posX = static_cast<int>(pos.x);
            int posY = static_cast<int>(pos.y);
            int height = static_cast<int>(size.y);
            int width = static_cast<int>(size.x);
            float unitWidth = size.x / 120.0F;
            float calcSpeed = unitWidth * static_cast<float>(speed);
            // Height always max, width should change based on speed
            DrawRectangle(posX, posY, calcSpeed, height, RED); //currentSpeed judges the bars width
        }
    }
};

#endif
