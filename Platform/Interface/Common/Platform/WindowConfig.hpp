#pragma once

#include <Platform/Cursor.hpp>
#include <Platform/Icon.hpp>
#include <Platform/Stl.hpp>

struct WindowConfig {
    static constexpr size_t MAX_RESOURCE_NAME_LENGTH = 100;

    std::array<char, MAX_RESOURCE_NAME_LENGTH> title;
    int32_t height;
    int32_t width;

    Icon appIcon_;
    Cursor mouseCursor_;
    bool showCursor_ = true;
    Icon smallAppIcon_;
    std::array<char, MAX_RESOURCE_NAME_LENGTH> mainWindowClassName_;
};
