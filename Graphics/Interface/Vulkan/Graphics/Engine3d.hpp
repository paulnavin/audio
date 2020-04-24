#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/ShaderBuffer.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexType.hpp>

class ResourceLocator;
class Window;

class Engine3d {
public:
    // TODO: Define move constructor/assignment?
    Engine3d() = default;
    ~Engine3d();

public:
    Result Init(const Window& newWindow, const ResourceLocator& resourceManager);
    Result InitGraphics(const VertexBuffer& buffer);
    void ClearBuffers();
    Result Present();
    Result RenderVertices();
    Result Resize();
    Result ToggleFullScreen();

    void NextDisplayConfig();
    void PreviousDisplayConfig();
    void ResetDisplayConfig();

private:
    Result CreateDxgiResources();
    Result InitShaders();
    Result LoadShader(const std::string& fileName, ShaderBuffer* shaderBuffer);
    Result InitSupportedDisplayModes();
};
