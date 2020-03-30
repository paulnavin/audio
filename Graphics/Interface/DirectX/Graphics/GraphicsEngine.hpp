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
    const Engine2d& GetEngine2d() const;
    const ResourceManager& GetResourceManager() const;
    const TextManager2d& GetTextManager2d() const;
    const Window* GetTargetWindow() const;

public:
    Result Init(Window* targetWindow, const ResourceManager& resourceManager);
    Result Init3dVertices(const VertexBuffer& vertexBuffer);
    void NextDisplayConfig();
    void PreviousDisplayConfig();
    void StartRender();
    void EndRender();
    void ResetDisplayConfig();
    void Resize();
    void ToggleFullScreen();

private:
    Engine2d engine2d_;
    Engine3d engine3d_;

    // TODO: Move this up higher, when it manages more than just graphics resources.
    ResourceManager resourceManager_;
    TextManager2d textManager2d_;
    Window* targetWindow_;
};
