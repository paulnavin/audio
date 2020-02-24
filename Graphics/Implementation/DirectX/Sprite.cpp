#include <Graphics/Sprite.hpp>

#include <Graphics/Engine2d.hpp>
#include <StringHandling/StringUtil.hpp>

Sprite::Sprite(Element* parent) : Element(parent) {

}

Result Sprite::Init(const Engine2d& engine, const TextManager2d& /*textManager*/) {
    deviceContext2d_ = engine.GetDeviceContext2d();

    imageFactory_ = engine.GetImageFactory();
    

    return Result{};
}

void Sprite::Render(const double&) {
    D2D1_SIZE_U size = bitmap_->GetPixelSize();

    D2D1_RECT_F sourceRect = { 0.0f, 0.0f, (float)size.width, (float)size.height };
    D2D1_RECT_F destRect = { position_.x, position_.y, position_.x + dimensions_.width, position_.y + dimensions_.height };
    D2D1_BITMAP_INTERPOLATION_MODE interPol = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
    float opacity = 1.0f;
    deviceContext2d_->DrawBitmap(bitmap_.Get(), destRect, opacity, interPol, sourceRect);
}

void Sprite::OnClick() {
}

Result Sprite::SetSourceFileName(const std::string& fileName) {
    Result result{};
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;

    std::wstring imageFileName = StringUtil::StringToWideString(fileName);
    HRESULT hr = imageFactory_->CreateDecoderFromFilename(imageFileName.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, bitmapDecoder.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::SetSourceFileName() : Error creating decoder from file name.");
        return result;
    }

    // get the correct frame
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    hr = bitmapDecoder->GetFrame(0, frame.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::SetSourceFileName() : Error creating sprite frame.");
        return result;
    }

    // create the format converter
    Microsoft::WRL::ComPtr<IWICFormatConverter> image;
    hr = imageFactory_->CreateFormatConverter(image.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::SetSourceFileName() : Error creating sprite image.");
        return result;
    }

    // initialize the WIC image
    hr = image->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) {
        result.AppendError("Sprite::SetSourceFileName() : Error initialising WIC image.");
        return result;
    }

    // create the bitmap
    hr = deviceContext2d_->CreateBitmapFromWicBitmap(image.Get(), bitmap_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("Sprite::SetSourceFileName() : Error creating bitmap image.");
        return result;
    }

    return result;
}