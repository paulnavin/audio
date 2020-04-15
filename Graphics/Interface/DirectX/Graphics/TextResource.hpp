#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>

struct Position2d;
struct Dimension2d;

class TextResource {
public:
    TextResource() = default;
    ~TextResource() = default;

public:
    Result Init(GraphicsEngine* gfx/*, const char* fontName*/);

    void Render();

public:
    void SetText(const std::string& newText);
    void SetPosition(const Position2d& position);
    void SetDimensions(const Dimension2d& dimensions);

private:
    void UpdateDetails();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    std::string                                  text_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    D2D1_POINT_2F                                textPosition_;
    float                                        textHeight_;
    float                                        textWidth_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
