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
    const Engine2d& engine = gfx->GetEngine2d();

    deviceContext2d_ = engine.GetDeviceContext2d();
    imageFactory_ = engine.GetImageFactory();
    strncpy_s(fileName_, MAX_FILE_PATH_LENGTH, fileName, strlen(fileName));

    return Result{};
}

Result BitmapResource::Load() {
    Result updateResult = LoadFromFile(fileName_);
    if (updateResult.HasErrors()) {
        updateResult.AppendError("BitmapResource::Load() : Couldn't load bitmap from disk");
        updateResult.AppendError(fileName_);
        return updateResult;
    }
    loaded_ = true;
    return updateResult;
}

bool BitmapResource::IsLoaded() const
{
    return loaded_;
}

Result BitmapResource::LoadFromFile(const char* fileName) {
    Result result{};
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;

    wchar_t imageFileName[MAX_FILE_PATH_LENGTH];
    StringUtil::StringToWideString(imageFileName, fileName, MAX_FILE_PATH_LENGTH);
    HRESULT hr = imageFactory_->CreateDecoderFromFilename(imageFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, bitmapDecoder.ReleaseAndGetAddressOf());
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
