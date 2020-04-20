#pragma once

#include <Platform/Stl.hpp>
#include <Graphics/Colour.hpp>

struct TextStyle {
    using Id = uint8_t;
    using Size = float;

    enum class HorizontalAlignment {
        Start,
        End,
        Centre
    };

    Id id;
    Colour colour;
    const char* fontName;
    Size size;
    HorizontalAlignment horizontalAlignment = HorizontalAlignment::Start;
};
