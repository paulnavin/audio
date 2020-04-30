#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Graphics/DirectXInterface.hpp>

struct Dimension2d;
struct Position2d;

class GraphicsEngine;

class BitmapResource {
public:
    BitmapResource() = default;
    ~BitmapResource() = default;

public:
    Microsoft::WRL::ComPtr<IWICFormatConverter> GetWicImage();

public:
    Result Init(GraphicsEngine* gfx, const char* fileName);

public:
    bool IsLoaded() const;

private:
    Result LoadFromFile(const char* fileName);

private:
    Microsoft::WRL::ComPtr<IWICFormatConverter> image_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory>  imageFactory_;
};
