#include <Graphics/Bitmap.hpp>

#include <Graphics/BitmapResource.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>

Result Bitmap::Init(GraphicsEngine* gfx, BitmapResource* resource) {
    Result initResult{};

    deviceContext2d_ = gfx->GetEngine2d().GetDeviceContext2d();

    Microsoft::WRL::ComPtr<IWICFormatConverter> wicImage = resource->GetWicImage();
    HRESULT hr = deviceContext2d_->CreateBitmapFromWicBitmap(wicImage.Get(), bitmap_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        initResult.AppendError("Bitmap::Init() : Error creating bitmap image.");
        return initResult;
    }

    return initResult;
}

void Bitmap::SetPositionAndDimension(const Position2d& position, const Dimension2d& dimensions) {
    D2D1_SIZE_U size = bitmap_->GetPixelSize();
    sourceRect_ = { 0.0f, 0.0f, (float)size.width, (float)size.height };
    destRect_ = {
        position.x,
        position.y,
        position.x + dimensions.width,
        position.y + dimensions.height
    };
}

void Bitmap::Render() {
    deviceContext2d_->DrawBitmap(bitmap_.Get(), destRect_, opacity_, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, sourceRect_);
}
