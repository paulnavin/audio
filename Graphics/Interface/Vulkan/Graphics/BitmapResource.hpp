#pragma once

#include <ErrorHandling/Result.hpp>

struct Dimension2d;
struct Position2d;

class GraphicsEngine;

class BitmapResource {
public:
    BitmapResource() = default;
    ~BitmapResource() = default;

public:
    Result Init(GraphicsEngine* gfx, const char* name);

private:
    Result LoadFromFile(const char* fileName);
};
