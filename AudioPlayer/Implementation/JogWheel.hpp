#pragma once

#include <Graphics/Colour.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Element.hpp>

#include <Utility/Result.hpp>

class Engine2d;

class JogWheel : public Element {

public:
    JogWheel(Element* parent);
    ~JogWheel() = default;

public:
    Result Init(const Engine2d& engine) override;
    void Render(const double& dt) override;

public:
    void Update(const double& dt);

    Result SetPositionColour(const Colour& newColour);
    Result SetSlipmatColour(const Colour& newColour);

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    
    D2D1_POINT_2F centrePoint_;
    float currentRotation_ = 0.0f;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> positionBrush_;
    Colour positionColour_;
    Microsoft::WRL::ComPtr<ID2D1EllipseGeometry> positionGeometry_;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> slipmatBrush_;
    Colour slipmatColour_;
    Microsoft::WRL::ComPtr<ID2D1EllipseGeometry> slipmatGeometry_;

    Microsoft::WRL::ComPtr<ID2D1GeometryGroup> jogWheel_;
    ID2D1Geometry* geometries_[2];
};
