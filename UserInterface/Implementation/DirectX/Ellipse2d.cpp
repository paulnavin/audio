#include <UserInterface/Ellipse2d.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Ellipse2d::Init(ModelPortal* portal) {
    deviceContext2d_ = portal->gfx->GetEngine2d().GetDeviceContext2d();
    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("Ellipse2d::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Element::Init(portal);
}

void Ellipse2d::Render(const double&) {
    Result renderResult{};

    // TODO: Update the centre and rectangle by overriding SetPosition().
    D2D1_POINT_2F centre = { positionOnScreen_.x, positionOnScreen_.y};
    D2D1_ELLIPSE ellipse = { centre, dimensionsOnScreen_.width, dimensionsOnScreen_.height };
    deviceContext2d_->DrawEllipse(&ellipse, brush_.Get(), 5);
}

Result Ellipse2d::SetColour(const Colour& newColour) {
    colour_ = newColour;

    if (IsInitialised() == true) {
        return UpdateDetails();
    }

    return Result{};
}

Result Ellipse2d::UpdateDetails() {
    HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
        D2D1::ColorF(colour_.red, colour_.green, colour_.blue, colour_.alpha), &brush_);
    Result updateResult{};
    if (FAILED(hr)) {
        updateResult.AppendError("Ellipse2d::SetColour() : Could not set colour for Ellipse 2D.");
    }
    return updateResult;
}
