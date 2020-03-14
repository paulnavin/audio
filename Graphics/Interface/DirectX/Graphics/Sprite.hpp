#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>

class Sprite : public Element {

public:
    Sprite(Element* parent);
    ~Sprite() = default;

public:
    Result Init(const GraphicsEngine& gfx) override;
    void Render(const double& dt) override;
    void OnClick() override;

public:
    virtual Result SetSourceFileName(const std::string& fileName);

protected:
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory> imageFactory_;
};
