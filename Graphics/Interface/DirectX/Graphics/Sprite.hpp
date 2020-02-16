#pragma once

#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>
#include <Graphics/Position2d.hpp>
#include <Utility/Result.hpp>

class Engine2d;

class Sprite : public Element {

public:
    Sprite(Element* parent);
    ~Sprite() = default;

public:
    Result Init(const Engine2d& engine, const TextManager2d& textManager) override;
    void Render(const double& dt) override;
    void OnClick() override;

public:
    virtual Result SetSourceFileName(const std::string& fileName);

protected:
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IWICImagingFactory> imageFactory_;
};
