#include <Resources/ResourceManager.hpp>

#include <FileSystem/ResourceLocator.hpp>
#include <Graphics/GraphicsEngine.hpp>

void ResourceManager::ShowOpenFileDialog() {
    
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
                initResult.AppendError("Could not load bitmap resource:");
                initResult.AppendError(resourceLocation.c_str());
                return initResult;
            }
        }
    }
    return Result{};
}
