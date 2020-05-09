#include <Graphics/Bitmap.hpp>

#include <Graphics/BitmapResource.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/GraphicsCommands.hpp>
#include <Graphics/Position2d.hpp>
#include <Platform/Commander.hpp>

Result Bitmap::Init(Commander* keen, GraphicsEngine* gfx, BitmapResource* resource) {
    Result result{};

    deviceContext2d_ = gfx->GetEngine2d().GetDeviceContext2d();
    keen_ = keen;
    resource_ = resource;

    if (resource_->IsLoaded() == true) {
        CreateBitmapFromResource();
    } else {
        ReturnIfHrError(
            deviceContext2d_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue, 1.0f), &brush_),
            "Bitmap::Init() : Error creating bitmap debug rectangle brush.");
        keen_->Subscribe(BitmapLoaded, this);
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

const bool Bitmap::IsEnabled() const {
    return true;
}

void Bitmap::HandleCommand(const CommandId& command) {
    if ((command == BitmapLoaded) && (resource_->IsLoaded() == true)) {
        CreateBitmapFromResource();
    }
}

Result Bitmap::CreateBitmapFromResource() {
    Result result{};
    Microsoft::WRL::ComPtr<IWICFormatConverter> wicImage = resource_->GetWicImage();
    ReturnIfHrError(
        deviceContext2d_->CreateBitmapFromWicBitmap(wicImage.Get(), bitmap_.ReleaseAndGetAddressOf()),
        "Bitmap::Init() : Error creating bitmap image.");
    D2D1_SIZE_U size = bitmap_->GetPixelSize();
    sourceRect_ = { 0.0f, 0.0f, (float)size.width, (float)size.height };
    drawBitmap_ = true;
    return result;
}