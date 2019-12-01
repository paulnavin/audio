#include <Ui/Ellipse2d.hpp>

#include <Ui/DirectXInterface.hpp>
#include <Ui/Engine2d.hpp>

class Ellipse2dInternals {
public:
    Result Init(const Engine2d& engine) {
        deviceContext2d_ = engine.GetDeviceContext2d();
        return Result{};
    }

    void Render() {
        Result renderResult{};
        D2D1_POINT_2F centre = { 700.0f, 500.0f };
        D2D1_ELLIPSE ellipse = { centre, 200, 75 };
        deviceContext2d_->DrawEllipse(&ellipse, brush_.Get(), 5);
    }

    Result SetColour(const Colour& newColour) {
        colour_ = newColour;

        HRESULT hr = deviceContext2d_->CreateSolidColorBrush(
            D2D1::ColorF(colour_.red, colour_.green, colour_.blue, colour_.alpha), &brush_);
        Result setResult{};
        if (FAILED(hr)) {
            setResult.AppendError("TextManager2d::InitialiseTextFormats() : Could not create brush for rectangle.");
        }
        return setResult;
    }

private:
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush_;
    Colour colour_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
};

Ellipse2d::Ellipse2d() {
    internals_ = new Ellipse2dInternals();
}

Ellipse2d::~Ellipse2d() {
    delete internals_;
}

Result Ellipse2d::Init(const Engine2d& engine) {
    return internals_->Init(engine);
}

void Ellipse2d::Render() {
    internals_->Render();
}

Result Ellipse2d::SetColour(const Colour& newColour) {
    return internals_->SetColour(newColour);
}
