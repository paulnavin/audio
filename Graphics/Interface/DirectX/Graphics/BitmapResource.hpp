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
    Result Load();

public:
    bool IsLoaded() const;

private:
    static constexpr size_t MAX_FILE_PATH_LENGTH = 512;
private:
    Result LoadFromFile(const char* fileName);

private:
    Microsoft::WRL::ComPtr<IWICFormatConverter> image_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory>  imageFactory_;
    bool loaded_ = false;
    // TODO: Pull MAX_FILE_PATH_LENGTH out to a shared constant.
    char fileName_[MAX_FILE_PATH_LENGTH];
};
