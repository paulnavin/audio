#include <Resources/ResourceManager.hpp>

#include <Graphics/GraphicsCommands.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Platform/Commander.hpp>
#include <Platform/ResourceLocator.hpp>

Result ResourceManager::Init(GraphicsEngine* gfx, Commander* keen) {
    gfx_ = gfx;
    keen_ = keen;
    return Result{};
}

void ResourceManager::ShutDown() {
    for (auto bitmap : bitties_) {
        delete bitmap;
    }

    for (auto resource : loadedBitmapResources_) {
        delete resource.second;
    }

    for (auto text : texties_) {
        delete text;
    }

    for (auto resource : loadedTextResources_) {
        delete resource.second;
    }

}

void ResourceManager::RegisterBitmapToLoad(const std::string& name) {
    namesToLoad_.push_back(name);
}

void ResourceManager::RegisterTextStyle(const TextStyle& newStyle) {
    stylesToLoad_.push_back(newStyle);
}

Bitmap* ResourceManager::GimmeABitmapDammit(const std::string& name) {
    BitmapResourceMap::iterator finder = loadedBitmapResources_.find(name);
    if (finder != loadedBitmapResources_.end()) {
        Bitmap* newBitmap = new Bitmap();
        Result initResult = newBitmap->Init(keen_, gfx_, finder->second);
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

Text* ResourceManager::GimmeATextBoxDammit(const TextStyle::Id& id) {
    UNREFERENCED_PARAMETER(id);
    TextResourceMap::iterator finder = loadedTextResources_.find(id);
    if (finder != loadedTextResources_.end()) {
        Text* newText = new Text();
        Result initResult = newText->Init(gfx_, finder->second);
        if (initResult.IsOkay()) {
            texties_.push_back(newText);
            return newText;
        } else {
            delete newText;
            initResult.AppendError("Could not get text.");
            return nullptr;
        }
    } else {
        return nullptr;
    }
    return nullptr;
}

Result ResourceManager::InitBitmaps() {
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
                initResult.AppendError("Could not init bitmap resource:");
                initResult.AppendError(resourceLocation.c_str());
                return initResult;
            }
        }
    }
    return Result{};
}

Result ResourceManager::LoadAllText() {
    for (TextStyle style : stylesToLoad_) {
        if (loadedTextResources_.find(style.id) == loadedTextResources_.end()) {
            TextResource* newResource = new TextResource();
            Result initResult = newResource->Init(gfx_, style);
            if (initResult.IsOkay()) {
                loadedTextResources_.insert(std::make_pair(style.id, newResource));
            } else {
                delete newResource;
                initResult.AppendError("Could not load text resource:");
                initResult.AppendError(style.fontName);
                return initResult;
            }
        }
    }
    return Result{};
}

Result ResourceManager::LoadAllBitmaps() {
    OutputDebugStringA("Started loading bitmaps!");
    for (BitmapNameResourcePair resource : loadedBitmapResources_) {
        resource.second->Load();
    }
    OutputDebugStringA("Finished loading bitmaps!");
    keen_->Distribute(BitmapLoaded);
    // TODO: Error handling here.
    return Result{};
}