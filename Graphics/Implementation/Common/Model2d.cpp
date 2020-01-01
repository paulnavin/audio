#include <Graphics/Model2d.hpp>

void Model2d::SetFps(const int64_t& newFps) {
    fps_ = newFps;
}

void Model2d::SetShowFps(const bool show) {
    showFps_ = show;
}

void Model2d::SetMousePosition(const int32_t& x, const int32_t& y) {
    mouseXPosition_ = x;
    mouseYPosition_ = y;
}

void Model2d::SetShowMousePosition(const bool show) {
    showMousePosition_ = show;
}
