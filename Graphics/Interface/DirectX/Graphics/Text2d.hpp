#pragma once

#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>

#include <ErrorHandling/Result.hpp>

class Engine2d;

class Text2d : public Element {

public:
    Text2d(Element* parent);
    ~Text2d() = default;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager) override;
    void Render(const double& dt) override;

public:
    Result SetText(const std::wstring& newText);

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    D2D1_POINT_2F                                textPosition_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
