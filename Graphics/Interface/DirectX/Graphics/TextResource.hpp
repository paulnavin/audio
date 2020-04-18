#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>

class GraphicsEngine;

struct Position2d;
struct Dimension2d;
struct TextStyle;

class TextResource {
public:
    TextResource() = default;
    ~TextResource() = default;

public:
    Result Init(GraphicsEngine* gfx, const TextStyle& style);

public:
    const Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>& GetBrush();
    const Microsoft::WRL::ComPtr<IDWriteTextFormat>& GetTextFormat();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
};
