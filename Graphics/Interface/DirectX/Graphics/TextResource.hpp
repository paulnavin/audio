#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>

class GraphicsEngine;

struct Position2d;
struct Dimension2d;

class TextResource {
public:
    TextResource() = default;
    ~TextResource() = default;

public:
    Result Init(GraphicsEngine* gfx/*, const char* fontName*/);

public:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> GetBrush();
    Microsoft::WRL::ComPtr<IDWriteTextFormat> GetTextFormat();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
};
