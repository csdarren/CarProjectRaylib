#ifndef DRAW_HPP
#define DRAW_HPP

#include "raylib.h"
class Draw {
  private:
    Model carModel{};
    static constexpr Vector3 CAR_POS = {0.0F, 0.0F, 0.0F};

  public:
    Draw() {
        this->carModel = LoadModel("../assets/models/MiniCooper.glb");
    }
    Draw(const Draw &) = default;
    Draw(Draw &&) = delete;
    auto operator=(const Draw &) -> Draw & = default;
    auto operator=(Draw &&) -> Draw & = delete;
    auto Car() -> void {
        for (int i = 0; i < carModel.materialCount; i++) {
            DrawModel(carModel, CAR_POS, 1.0F, WHITE);
        }
    }
    ~Draw() {
        UnloadModel(carModel);
    }
};

#endif
