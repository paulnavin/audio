#pragma once

#include <Stl/StlWrapper.hpp>
#include <Graphics/Colour.hpp>

struct TextStyle {
    using Id = uint8_t;
    using Size = float;

    Id id;
    Colour colour;
    const char* fontName;
    Size size;
};
