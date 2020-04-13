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
}

void ResourceManager::RegisterBitmapToLoad(const std::string& name) {
    namesToLoad_.push_back(name);
}

void ResourceManager::RegisterTextToLoad(const char* /*styleName*/) {
    
}

BitmapResource* ResourceManager::GimmeABitmapDammit(const std::string& name) {
    BitmapResourceMap::iterator finder = loadedBitmapResources_.find(name);
    if (finder != loadedBitmapResources_.end()) {
        return finder->second;
    } else {
        return nullptr;
    }
}
TextBox* ResourceManager::GimmeATextBoxDammit(const char* /*styleName*/) {
    return nullptr;
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
                initResult.AppendError("Could not load bitmap:");
                initResult.AppendError(resourceLocation.c_str());
                return initResult;
            }
        }
    }
    return Result{};
}
