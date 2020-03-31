#pragma once

#include <Graphics/DirectXInterface.hpp>
#include <ErrorHandling/Result.hpp>
#include <UserInterface/Element.hpp>

class Sprite : public Element {

public:
    Sprite() = default;
    virtual ~Sprite() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;

public:
    virtual Result SetSourceFileName(const std::string& fileName);

private:
    Result UpdateDetails();

protected:
    Microsoft::WRL::ComPtr<ID2D1Bitmap1>        bitmap_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory>  imageFactory_;
    std::string                                 sourceFileName_;
};
