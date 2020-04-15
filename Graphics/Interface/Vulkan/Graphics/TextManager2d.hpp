#pragma once

#include <ErrorHandling/Result.hpp>

class Engine2d;
class Window;

class TextManager2d {

public:
    TextManager2d() = default;
    ~TextManager2d() = default;

public:
    Result Init(const Window& newWindow, const Engine2d& newEngine);
    Result InitialiseFactory();
    Result InitialiseTextFormats();
    Result Resize();
};
