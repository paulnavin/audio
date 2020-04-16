#include <Resources/ResourceManager.hpp>

#include <FileSystem/ResourceLocator.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Platform/WindowsInterface.hpp>
#include <StringHandling/StringUtil.hpp>

void ResourceManager::ShowOpenFileDialog() {
    std::string fileName;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr)) {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr)) {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    std::wstring returnedFileName(pszFilePath);
                    fileName = StringUtil::WideStringToString(returnedFileName);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr)) {
                        MessageBoxA(NULL, fileName.c_str(), "File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
}

Result ResourceManager::Init(GraphicsEngine* gfx) {
    gfx_ = gfx;
    return Result{};
}

void ResourceManager::ShutDown() {
    for (auto resource : loadedBitmapResources_) {
        delete resource.second;
    }

    for (auto bitmap : bitties_) {
        delete bitmap;
    }
}

void ResourceManager::RegisterBitmapToLoad(const std::string& name) {
    namesToLoad_.push_back(name);
}

void ResourceManager::RegisterTextToLoad(const char* /*styleName*/) {

}

Bitmap* ResourceManager::GimmeABitmapDammit(const std::string& name) {
    BitmapResourceMap::iterator finder = loadedBitmapResources_.find(name);
    if (finder != loadedBitmapResources_.end()) {
        Bitmap* newBitmap = new Bitmap();
        Result initResult = newBitmap->Init(gfx_, finder->second);
        if (initResult.IsOkay()) {
            bitties_.push_back(newBitmap);
            return newBitmap;
        } else {
            delete newBitmap;
            initResult.AppendError("Could not get bitmap:");
            initResult.AppendError(name.c_str());
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

Text* ResourceManager::GimmeATextBoxDammit(const char* /*styleName*/) {
    size_t textBoxCountBefore = textBoxCount_;
    textBoxes_[textBoxCountBefore].Init(gfx_, &textResources_[0]);
    ++textBoxCount_;
    return &textBoxes_[textBoxCountBefore];
}

Result ResourceManager::LoadBitmaps() {
    const ResourceLocator& resourceLocator = gfx_->GetResourceLocator();
    for (std::string name : namesToLoad_) {
        if (loadedBitmapResources_.find(name) == loadedBitmapResources_.end()) {
            std::string fullFileName(name);
            fullFileName.append(".png");
            std::string resourceLocation = resourceLocator.GetFullImageFileName(fullFileName);

            BitmapResource* newResource = new BitmapResource();
            Result initResult = newResource->Init(gfx_, resourceLocation.c_str());
            if (initResult.IsOkay()) {
                loadedBitmapResources_.insert(std::make_pair(name, newResource));
            } else {
                delete newResource;
                initResult.AppendError("Could not load bitmap resource:");
                initResult.AppendError(resourceLocation.c_str());
                return initResult;
            }
        }
    }
    return Result{};
}

Result ResourceManager::LoadAllText() {
    textResources_[0].Init(gfx_);
    return Result{};
}
