#pragma once

#include <ErrorHandling/Result.hpp>

class BitmapResource;

class Bitmap {
public:
    Bitmap() = default;
    ~Bitmap() = default;

public:
    Result Init(BitmapResource* resource);

private:
};
