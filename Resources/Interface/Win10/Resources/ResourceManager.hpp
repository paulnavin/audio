#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Bitmap.hpp>
#include <Graphics/BitmapResource.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/TextResource.hpp>

class GraphicsEngine;

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    static void ShowOpenFileDialog();

public:
    Result Init(GraphicsEngine* gfx);
    void ShutDown();

public:
    void RegisterBitmapToLoad(const std::string& name);
    void RegisterTextToLoad(const char* styleName);

    Bitmap* GimmeABitmapDammit(const std::string& name);
    Text* GimmeATextBoxDammit(const char* styleName);

    Result LoadBitmaps();
    Result LoadAllText();

private:
    using BitmapResourceMap = std::map<std::string, BitmapResource*>;
    using Bitmaps = std::vector<Bitmap*>;

private:
    GraphicsEngine* gfx_;

    std::vector<std::string> namesToLoad_;
    BitmapResourceMap loadedBitmapResources_;
    Bitmaps bitties_;

    std::string textNames_[10];
    std::string textStyles_[10];
    TextResource textResources_[10];
    Text textBoxes_[20];
    size_t textResourceCount_ = 0;
    size_t textBoxCount_ = 0;
};
