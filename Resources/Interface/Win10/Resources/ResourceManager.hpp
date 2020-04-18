#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Bitmap.hpp>
#include <Graphics/BitmapResource.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/TextResource.hpp>
#include <Graphics/TextStyle.hpp>

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
    void RegisterTextStyle(const TextStyle& newStyle);

    Bitmap* GimmeABitmapDammit(const std::string& name);
    Text* GimmeATextBoxDammit(const TextStyle::Id& id);

    Result LoadBitmaps();
    Result LoadAllText();

private:
    using BitmapNames = std::vector<std::string>;
    using BitmapResourceMap = std::map<std::string, BitmapResource*>;
    using Bitmaps = std::vector<Bitmap*>;

    using TextStyles = std::vector<TextStyle>;
    using TextResourceMap = std::map<TextStyle::Id, TextResource*>;
    using Texts = std::vector<Text*>;

private:
    GraphicsEngine* gfx_;

    BitmapNames namesToLoad_;
    BitmapResourceMap loadedBitmapResources_;
    Bitmaps bitties_;

    TextStyles stylesToLoad_;
    TextResourceMap loadedTextResources_;
    Texts texties_;
};
