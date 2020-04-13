#pragma once

#include <ErrorHandling/Result.hpp>

class TextResource;

class TextBox {
public:
    TextBox() = default;
    ~TextBox() = default;

public:
    Result Init(const TextResource& resource);

private:
};
