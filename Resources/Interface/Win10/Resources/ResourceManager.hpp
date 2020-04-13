#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Bitmap.hpp>
#include <Graphics/BitmapResource.hpp>
#include <Graphics/TextBox.hpp>
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
    TextBox* GimmeATextBoxDammit(const char* styleName);

    Result LoadBitmaps();

private:
    using BitmapResourceMap = std::map<std::string, BitmapResource*>;
    using Bitmaps = std::vector<Bitmap*>;

private:
    GraphicsEngine* gfx_;

    std::vector<std::string> namesToLoad_;
    BitmapResourceMap loadedBitmapResources_;
    Bitmaps bitties_;

    std::string bitmapNames_[10];
    std::string bitmapPaths_[10];
    BitmapResource bitmapResources_[10];
    Bitmap bitmaps_[10];
    size_t bitmapResourceCount_ = 0;
    size_t bitmapCount_ = 0;
    size_t bitmapsToLoadCount_ = 0;

    std::string textNames_[10];
    std::string textPaths_[10];
    TextResource textResources[10];
    TextBox textBoxes_[10];
    size_t textResourceCount_ = 0;
    size_t textBoxCount_ = 0;
};
