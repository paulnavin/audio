#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/Engine3d.hpp>
#include <Graphics/TextManager2d.hpp>
#include <FileSystem/ResourceManager.hpp>
#include <ErrorHandling/Result.hpp>

class Model2d;
class Model3d;
class ResourceManager;
class Window;

class GraphicsEngine {

public:
    GraphicsEngine() = default;
    ~GraphicsEngine() = default;

public:
    Result Init(const Window& targetWindow, const ResourceManager& resourceManager);
    Result Init2dModel(Model2d* model);
    void NextDisplayConfig();
    void PreviousDisplayConfig();
    void Render(const double& dt);
    void ResetDisplayConfig();
    void Resize();
    Result Set2dModel(Model2d* model);
    Result Set3dModel(const Model3d& model);
    void ToggleFullScreen();

private:
    Engine2d engine2d_;
    Engine3d engine3d_;
    ResourceManager resourceManager_;
    TextManager2d textManager2d_;
};
