#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Platform/Stl.hpp>
#include <Graphics/Bitmap.hpp>
#include <Graphics/BitmapResource.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/TextResource.hpp>
#include <Graphics/TextStyle.hpp>

class Commander;
class GraphicsEngine;

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    Result Init(GraphicsEngine* gfx, Commander*);
    void ShutDown();

public:
    void RegisterBitmapToLoad(const std::string& name);
    void RegisterTextStyle(const TextStyle& newStyle);

    Bitmap* GimmeABitmapDammit(const std::string& name);
    Text* GimmeATextBoxDammit(const TextStyle::Id& id);

    Result InitBitmaps();
    Result LoadAllText();
    Result LoadAllBitmaps();

private:
    using BitmapNames = std::vector<std::string>;
    using BitmapResourceMap = std::map<std::string, BitmapResource*>;
    using Bitmaps = std::vector<Bitmap*>;
    using BitmapNameResourcePair = std::pair<std::string, BitmapResource*>;

    using TextStyles = std::vector<TextStyle>;
    using TextResourceMap = std::map<TextStyle::Id, TextResource*>;
    using Texts = std::vector<Text*>;

private:
    Commander* keen_;
    GraphicsEngine* gfx_;

    BitmapNames namesToLoad_;
    BitmapResourceMap loadedBitmapResources_;
    Bitmaps bitties_;

    TextStyles stylesToLoad_;
    TextResourceMap loadedTextResources_;
    Texts texties_;
};
