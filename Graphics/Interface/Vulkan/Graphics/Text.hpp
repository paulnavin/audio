#pragma once

#include <ErrorHandling/Result.hpp>

class TextResource;

class Text {
public:
    Text() = default;
    ~Text() = default;

public:
    Result Init(const TextResource& resource);

private:
};
