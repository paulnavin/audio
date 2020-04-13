#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>

struct Dimension2d;
struct Position2d;

class GraphicsEngine;

class BitmapResource {
public:
    BitmapResource() = default;
    ~BitmapResource() = default;

public:
    Result Init(GraphicsEngine* gfx, const char* name);
    void Render(const Position2d& position, const Dimension2d& dimensions);

private:
    Result LoadFromFile(const char* fileName);

private:
    Microsoft::WRL::ComPtr<ID2D1Bitmap1>        bitmap_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory>  imageFactory_;
};
