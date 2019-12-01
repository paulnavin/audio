#pragma once

#include <Ui/Colour.hpp>
#include <Ui/Result.hpp>

class Ellipse2dInternals;
class Engine2d;

class Ellipse2d {

public:
    Ellipse2d();
    ~Ellipse2d();

public:
    Result Init(const Engine2d& engine);
    void Render();
    Result SetColour(const Colour& newColour);

private:
    Ellipse2dInternals* internals_;
};
