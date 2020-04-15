#pragma once

#include <ErrorHandling/Result.hpp>

class GraphicsEngine;
class TextResource;
struct Position2d;
struct Dimension2d;

class Text {
public:
    Text() = default;
    ~Text() = default;

public:
    Result Init(GraphicsEngine* gfx, TextResource* resource);

    void Render();

public:
    void SetText(const std::string& newText);
    void SetPosition(const Position2d& position);
    void SetDimensions(const Dimension2d& dimensions);

private:
    TextResource* textResource_;
};
