#include <UserInterface/Sprite.hpp>

#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <StringHandling/StringUtil.hpp>

Result Sprite::Init(const GraphicsEngine& gfx) {
    const Engine2d& engine = gfx.GetEngine2d();

    deviceContext2d_ = engine.GetDeviceContext2d();
    imageFactory_ = engine.GetImageFactory();

    Result updateResult = UpdateDetails();
    if (updateResult.HasErrors()) {
        updateResult.AppendError("Sprite::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Element::Init(gfx);
}

void Sprite::Render(const double&) {
    D2D1_SIZE_U size = bitmap_->GetPixelSize();

    D2D1_RECT_F sourceRect = { 0.0f, 0.0f, (float)size.width, (float)size.height };
    D2D1_RECT_F destRect = { positionOnScreen_.x, positionOnScreen_.y, positionOnScreen_.x + dimensionsOnScreen_.width, positionOnScreen_.y + dimensionsOnScreen_.height };
    D2D1_BITMAP_INTERPOLATION_MODE interPol = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
    float opacity = 1.0f;
    deviceContext2d_->DrawBitmap(bitmap_.Get(), destRect, opacity, interPol, sourceRect);
}

Result Sprite::SetSourceFileName(const std::string& fileName) {
    sourceFileName_ = fileName;

    if (IsInitialised() == true) {
        return UpdateDetails();
    }
    return Result{};
}

Result Sprite::UpdateDetails() {
    Result result{};
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;

    std::wstring imageFileName = StringUtil::StringToWideString(sourceFileName_);
    HRESULT hr = imageFactory_->CreateDecoderFromFilename(imageFileName.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, bitmapDecoder.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::UpdateDetails() : Error creating decoder from file name.");
        return result;
    }

    // get the correct frame
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    hr = bitmapDecoder->GetFrame(0, frame.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::UpdateDetails() : Error creating sprite frame.");
        return result;
    }

    // create the format converter
    Microsoft::WRL::ComPtr<IWICFormatConverter> image;
    hr = imageFactory_->CreateFormatConverter(image.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::UpdateDetails() : Error creating sprite image.");
        return result;
    }

    // initialize the WIC image
    hr = image->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) {
        result.AppendError("Sprite::UpdateDetails() : Error initialising WIC image.");
        return result;
    }

    // create the bitmap
    hr = deviceContext2d_->CreateBitmapFromWicBitmap(image.Get(), bitmap_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::UpdateDetails() : Error creating bitmap image.");
        return result;
    }

    return result;
}