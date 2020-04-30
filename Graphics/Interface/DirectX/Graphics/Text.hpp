#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Graphics/DirectXInterface.hpp>

class GraphicsEngine;
class TextResource;
struct Position2d;
struct Dimension2d;

class Text {
public:
    Text() = default;
    ~Text() = default;

public:
    Result Init(GraphicsEngine* gfx, TextResource* resource);

    void Render();
    void RenderText(const std::string& text);

public:
    void SetText(const std::string& newText);
    void SetPosition(const Position2d& position);
    void SetDimensions(const Dimension2d& dimensions);

private:
    void UpdateTextLayout();

private:
    TextResource* textResource_;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    std::string                                  text_;
    D2D1_POINT_2F                                textPosition_;
    float                                        textHeight_;
    float                                        textWidth_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
