#pragma once

#include <ErrorHandling/Result.hpp>

class Cursor {
public:
    Cursor() = default;
    ~Cursor() = default;

public:
    Result Init();
};
