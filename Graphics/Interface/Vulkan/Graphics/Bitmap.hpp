#pragma once

#include <ErrorHandling/Result.hpp>

struct Dimension2d;
struct Position2d;

class BitmapResource;
class GraphicsEngine;

class Bitmap {
public:
    Bitmap() = default;
    ~Bitmap() = default;

public:
    Result Init(GraphicsEngine* gfx, BitmapResource* resource);

    void SetPositionAndDimension(const Position2d& position, const Dimension2d& dimensions);
    void Render();
};
