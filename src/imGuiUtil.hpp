#pragma once
#ifndef IMGUIUTIL_HPP
#define IMGUIUTIL_HPP

ImVec2 ImVec2Divide(ImVec2 vec, float divisor) {
    return ImVec2{vec.x / divisor, vec.y / divisor};
}
ImVec2 ImVec2Divide2(ImVec2 vec, float divisor1, float divisor2) {
    return ImVec2{vec.x / divisor1, vec.y / divisor2};
}
ImVec2 ImVec2Multiply(ImVec2 vec, int x) {
    return ImVec2{vec.x * x, vec.y * x};
}
ImVec2 ImVec2Multiply2(ImVec2 vec, int x, int y) {
    return ImVec2{vec.x * x, vec.y * y};
}
ImVec2 ImVec2Add(ImVec2 vec, int x) {
    return ImVec2{vec.x + x, vec.y + x};
}
ImVec2 ImVec2Add2(ImVec2 vec, int x, int y) {
    return ImVec2{vec.x + x, vec.y + y};
}
ImVec2 ImVec2Subtract(ImVec2 vec, int x) {
    return ImVec2{vec.x - x, vec.y + x};
}
ImVec2 ImVec2Subtract2(ImVec2 vec, int x, int y) {
    return ImVec2{vec.x - x, vec.y + y};
}
ImVec2 ImVecSubtractVec(ImVec2 vec1, ImVec2 vec2) {
    return ImVec2{vec1.x - vec2.x, vec1.y - vec2.y};
}
void ImVec2RlScissor(ImVec2 windowPos, ImVec2 windowSize) {
    rlEnableScissorTest();
    BeginScissorMode(windowPos.x, GetScreenHeight() - (int)(windowPos.y + windowSize.y) + 100, windowSize.x, windowSize.y);
}

#endif