#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <UserInterface/Element.hpp>

class Text2d : public Element {

public:
    Text2d() = default;
    virtual ~Text2d() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;

public:
    Result SetText(const std::string& newText);

private:
    Result UpdateDetails();

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    std::string                                  text_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat>    textFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout>    textLayout_;
    D2D1_POINT_2F                                textPosition_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
