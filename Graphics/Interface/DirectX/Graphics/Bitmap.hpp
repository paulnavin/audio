#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>

struct Dimension2d;
struct Position2d;

class BitmapResource;
class GraphicsEngine;

class Bitmap {
public:
    Bitmap() = default;
    ~Bitmap() = default;

public:
    Result Init(GraphicsEngine* gfx, BitmapResource* resource);

    void SetPositionAndDimension(const Position2d& position, const Dimension2d& dimensions);
    void Render();

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap_;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    D2D1_SIZE_U size_;
    D2D1_RECT_F sourceRect_;
    D2D1_RECT_F destRect_;
    float opacity_ = 1.0f;
    bool drawBitmap_ = false;
};
