#ifndef DRAW_HPP
#define DRAW_HPP

#include "raylib.h"
#include "raymath.h"
class Draw {
  private:
    Model carModel{};
    bool drawCar{false};

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

    auto toggleCarState() -> void {
        this->drawCar = !this->drawCar;
    }
    static auto Floor() -> void {
        DrawPlane(Vector3Zero(), FLOOR_SIZE, GRAY);
    }

    auto Car() -> void {
        if (drawCar) {
            for (int i = 0; i < carModel.materialCount; i++) {
                DrawModel(carModel, CAR_POS, 1.0F, WHITE);
            }
        }
    }
};

#endif
