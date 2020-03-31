#include "JogWheel.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Engine2d.hpp>
#include <Platform/WindowsInterface.hpp>
#include <UserInterface/ModelPortal.hpp>

Result JogWheel::Init(ModelPortal* portal) {
    const Engine2d& engine = portal->gfx->GetEngine2d();
    Microsoft::WRL::ComPtr<ID2D1Factory2> factory = engine.GetFactory();

    deviceContext2d_ = engine.GetDeviceContext2d();

    Result initResult{};

    centrePoint_ = { 256.0f, 300.0f };
    D2D1_ELLIPSE unitEllipse = { centrePoint_, 75.0f, 75.0f };
    HRESULT hr = factory->CreateEllipseGeometry(&unitEllipse, slipmatGeometry_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("JogWheel::Init() : Could not create geometry for slipmat.");
        return initResult;
    }

    D2D1_ELLIPSE positionEllipse = { {256.0f, 378.0f} , 10.0f, 10.0f };
    hr = factory->CreateEllipseGeometry(&positionEllipse, positionGeometry_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("JogWheel::Init() : Could not create geometry for position indicator.");
        return initResult;
    }

    geometries_[0] = slipmatGeometry_.Get();
    geometries_[1] = positionGeometry_.Get();

    hr = factory->CreateGeometryGroup(D2D1_FILL_MODE_WINDING, geometries_, ARRAYSIZE(geometries_), jogWheel_.GetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("JogWheel::Init() : Could not create geometry group for jog wheel.");
        return initResult;
    }

    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("JogWheel::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Element::Init(portal);
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

    if (IsInitialised() == true) {
        return UpdateDetails();
    }
    return Result{};
}

Result JogWheel::SetSlipmatColour(const Colour& newColour) {
    slipmatColour_ = newColour;

    if (IsInitialised() == true) {
        return UpdateDetails();
    }
    return Result{};
}

Result JogWheel::UpdateDetails() {
    Result updateResult{};

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(slipmatColour_.red, slipmatColour_.green, slipmatColour_.blue, slipmatColour_.alpha), &slipmatBrush_);
    if (FAILED(hr)) {
        updateResult.AppendError("JogWheel::UpdateDetails() : Could not create brush for slipmat.");
        return updateResult;
    }

    hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(positionColour_.red, positionColour_.green, positionColour_.blue, positionColour_.alpha), &positionBrush_);
    if (FAILED(hr)) {
        updateResult.AppendError("JogWheel::UpdateDetails() : Could not create brush for position indicator.");
        return updateResult;
    }

    return Result{};
}
