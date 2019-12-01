#pragma once

#include <Ui/Colour.hpp>
#include <Ui/DirectXInterface.hpp>

#include <Ui/Result.hpp>

class Engine2d;
class Rectangle2dInternals;

class Rectangle2d {

public:
    Rectangle2d();
    ~Rectangle2d();

public:
    Result Init(const Engine2d& engine);
    void Render();
    Result SetColour(const Colour& newColour);

private:
    Rectangle2dInternals* internals_;
};
