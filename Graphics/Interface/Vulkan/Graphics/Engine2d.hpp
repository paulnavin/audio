#pragma once

#include <Graphics/TextManager2d.hpp>

#include <ErrorHandling/Result.hpp>

class Engine3d;
class Model2d;
class Window;

class Engine2d {
public:
    Engine2d() = default;
    ~Engine2d() = default;

public:
    Result Init(const Window& newWindow, const Engine3d& newEngine);
    Result PrepareForResize();
    Result Resize();
    void StartRender();
    void EndRender();

private:
    Result CreateDevice();
    Result CreateBitmapRenderTarget();
    Result CreateImageFactory();
};
