#include <UserInterface/Rectangle2d.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Rectangle2d::Init(ModelPortal* portal) {
    deviceContext2d_ = portal->gfx->GetEngine2d().GetDeviceContext2d();
    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("Rectangle2d::Init() : Couldn't update details in Init()");
        return updateResult;
    }

    // TODO: Should this be above, before UpdateDetails()?
    return Element::Init(portal);
}

void Rectangle2d::Render(const double&) {
    rectangle_ = { positionOnScreen_.x, positionOnScreen_.y, positionOnScreen_.x + dimensionsOnScreen_.width, positionOnScreen_.y + dimensionsOnScreen_.height };
    deviceContext2d_->FillRectangle(&rectangle_, brush_.Get());
}

const Colour& Rectangle2d::GetColour() const {
    return colour_;
}

Result Rectangle2d::SetColour(const Colour& newColour) {
    colour_ = newColour;

    if (IsInitialised() == true) {
        return UpdateDetails();
    }

    return Result{};
}

Result Rectangle2d::UpdateDetails() {
    Result updateResult{};

    D2D1::ColorF mainColour = D2D1::ColorF(colour_.red, colour_.green, colour_.blue, colour_.alpha);
    D2D1::ColorF fadeColour = D2D1::ColorF(colour_.red, colour_.green, colour_.blue, 0.0f);

    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(mainColour, &brush_);
    if (FAILED(hr)) {
        updateResult.AppendError("Rectangle2d::SetColour() : Could not create brush for rectangle.");
    }

    Microsoft::WRL::ComPtr<ID2D1GradientStopCollection> stopCollection;
    D2D1_GRADIENT_STOP stops[] = {
        { 0.0f, D2D1::ColorF(fadeColour) },
        { 0.5f, D2D1::ColorF(mainColour)},
        { 1.0f, D2D1::ColorF(fadeColour) }
    };
    hr = deviceContext2d_->CreateGradientStopCollection(stops, _countof(stops), stopCollection.GetAddressOf());
    if (FAILED(hr)) {
        updateResult.AppendError("Rectangle2d::SetColour() : Could not create highlight stops.");
    }

    D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES linearGradientBrushProperties = {};
    hr = deviceContext2d_->CreateLinearGradientBrush(linearGradientBrushProperties, stopCollection.Get(), highlightBrush_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        updateResult.AppendError("Rectangle2d::SetColour() : Could not create linear gradient brush.");
    }

    return updateResult;
}
