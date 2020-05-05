#pragma once

#include <Graphics/DirectXInterface.hpp>
#include <Platform/ErrorHandling.hpp>

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
    void RenderText(const char* text);

public:
    void SetText(const char* newText);
    void SetPosition(const Position2d& position);
    void SetDimensions(const Dimension2d& dimensions);

private:
    void UpdateTextLayout();

private:
    static const size_t MAX_STRING_LENGTH = 512;

private:
    TextResource* textResource_;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    wchar_t                                      text_[MAX_STRING_LENGTH];
    D2D1_POINT_2F                                textPosition_;
    float                                        textHeight_;
    float                                        textWidth_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
