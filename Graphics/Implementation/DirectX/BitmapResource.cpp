#include <Graphics/BitmapResource.hpp>

#include <Graphics/Dimension2d.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <Platform/StringHandling.hpp>

Microsoft::WRL::ComPtr<IWICFormatConverter> BitmapResource::GetWicImage() {
    return image_;
}

Result BitmapResource::Init(GraphicsEngine* gfx, const char* fileName) {
    Result initResult{};

    const Engine2d& engine = gfx->GetEngine2d();

    deviceContext2d_ = engine.GetDeviceContext2d();
    imageFactory_ = engine.GetImageFactory();

    Result updateResult = LoadFromFile(fileName);
    if (updateResult.HasErrors()) {
        updateResult.AppendError("Sprite::Init() : Couldn't update details in Init()");
        return updateResult;
    }
    return Result{};
}

bool BitmapResource::IsLoaded() const
{
    return false;
}

Result BitmapResource::LoadFromFile(const char* fileName) {
    Result result{};
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;

    std::wstring imageFileName = StringUtil::StringToWideString(fileName);
    HRESULT hr = imageFactory_->CreateDecoderFromFilename(imageFileName.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, bitmapDecoder.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("BitmapResource::LoadFromFile() : Error creating decoder from file name.");
        return result;
    }

    // get the correct frame
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    hr = bitmapDecoder->GetFrame(0, frame.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("BitmapResource::LoadFromFile() : Error creating sprite frame.");
        return result;
    }

    // create the format converter
    hr = imageFactory_->CreateFormatConverter(image_.ReleaseAndGetAddressOf());
    if (FAILED(hr)) {
        result.AppendError("BitmapResource::LoadFromFile() : Error creating sprite image.");
        return result;
    }

    // initialize the WIC image
    hr = image_->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) {
        result.AppendError("BitmapResource::LoadFromFile() : Error initialising WIC image.");
        return result;
    }

    return result;
}
