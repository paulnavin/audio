#include "JogWheel.hpp"

#include <Graphics/Engine2d.hpp>
#include <UserInterface/WindowsInterface.hpp>

Result JogWheel::Init(const Engine2d& engine) {
    deviceContext2d_ = engine.GetDeviceContext2d();

    centrePoint_ = { 256.0f, 300.0f };
    D2D1_ELLIPSE unitEllipse = { centrePoint_, 75.0f, 75.0f };
    Result initResult{};
    Microsoft::WRL::ComPtr<ID2D1Factory2> factory = engine.GetFactory();
    HRESULT hr = factory->CreateEllipseGeometry(&unitEllipse, slipmatGeometry_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("RotatableEllipse2d::Init() : Could not create geometry for slipmat.");
    }

    D2D1_ELLIPSE positionEllipse = { {256.0f, 378.0f} , 10.0f, 10.0f };
    hr = factory->CreateEllipseGeometry(&positionEllipse, positionGeometry_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("RotatableEllipse2d::Init() : Could not create geometry for position indicator.");
    }

    geometries_[0] = slipmatGeometry_.Get();
    geometries_[1] = positionGeometry_.Get();

    hr = factory->CreateGeometryGroup(D2D1_FILL_MODE_WINDING, geometries_, ARRAYSIZE(geometries_), jogWheel_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("RotatableEllipse2d::Init() : Could not create geometry  group for jog wheel.");
    }

    return Result{};
}

void JogWheel::Update(const double& dt) {
    static constexpr double DEGREES_PER_SECOND = 360;
    float degreesPerFrame = static_cast<float>(DEGREES_PER_SECOND / 1000 * dt);
    currentRotation_ += degreesPerFrame;
    if (currentRotation_ >= 360.0f) {
        currentRotation_ -= 360.0f;
    }
}

void JogWheel::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);

    // Draw a non-moving one for comparison.
    deviceContext2d_->DrawGeometry(jogWheel_.Get(), slipmatBrush_.Get());
    deviceContext2d_->FillGeometry(jogWheel_.Get(), positionBrush_.Get());

    // Rotate that mofo.
    D2D_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(currentRotation_, centrePoint_);
    deviceContext2d_->SetTransform(rotation);
    deviceContext2d_->DrawGeometry(jogWheel_.Get(), slipmatBrush_.Get());
    deviceContext2d_->FillGeometry(jogWheel_.Get(), positionBrush_.Get());
    deviceContext2d_->SetTransform(D2D1::Matrix3x2F::Identity());
}

Result JogWheel::SetPositionColour(const Colour& newColour) {
    positionColour_ = newColour;

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(positionColour_.red, positionColour_.green, positionColour_.blue, positionColour_.alpha), &positionBrush_);
    Result setResult{};
    if (FAILED(hr)) {
        setResult.AppendError("RotatableEllipse2d::SetColour() : Could not create brush for position indicator.");
    }
    return setResult;
}

Result JogWheel::SetSlipmatColour(const Colour& newColour) {
    slipmatColour_ = newColour;

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(slipmatColour_.red, slipmatColour_.green, slipmatColour_.blue, slipmatColour_.alpha), &slipmatBrush_);
    Result setResult{};
    if (FAILED(hr)) {
        setResult.AppendError("RotatableEllipse2d::SetColour() : Could not create brush for slipmat.");
    }
    return setResult;
}
