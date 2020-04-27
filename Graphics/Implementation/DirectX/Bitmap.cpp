#include <Graphics/Bitmap.hpp>

#include <Graphics/BitmapResource.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>

Result Bitmap::Init(GraphicsEngine* gfx, BitmapResource* resource) {
    Result result{};

    deviceContext2d_ = gfx->GetEngine2d().GetDeviceContext2d();

    if (resource->IsLoaded() == true) {
        Microsoft::WRL::ComPtr<IWICFormatConverter> wicImage = resource->GetWicImage();
        ReturnIfHrError(
            deviceContext2d_->CreateBitmapFromWicBitmap(wicImage.Get(), bitmap_.ReleaseAndGetAddressOf()),
            "Bitmap::Init() : Error creating bitmap image.");
        D2D1_SIZE_U size = bitmap_->GetPixelSize();
        sourceRect_ = { 0.0f, 0.0f, (float)size.width, (float)size.height };
        drawBitmap_ = true;
    } else {
        ReturnIfHrError(
            deviceContext2d_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue, 1.0f), &brush_),
            "Bitmap::Init() : Error creating bitmap debug rectangle brush.");
    }

    return result;
}

void Bitmap::SetPositionAndDimension(const Position2d& position, const Dimension2d& dimensions) {
    destRect_ = {
        position.x,
        position.y,
        position.x + dimensions.width,
        position.y + dimensions.height
    };
}

void Bitmap::Render() {
    if (drawBitmap_ == true) {
        deviceContext2d_->DrawBitmap(bitmap_.Get(), destRect_, opacity_, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, sourceRect_);
    } else {
        deviceContext2d_->DrawRectangle(&destRect_, brush_.Get());
    }
}
