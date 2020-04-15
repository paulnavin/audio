#pragma once

#include <ErrorHandling/Result.hpp>

class TextResource {
public:
    TextResource() = default;
    ~TextResource() = default;

public:
    Result Init(const char* fontName);

private:
};
