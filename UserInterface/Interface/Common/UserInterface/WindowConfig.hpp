#pragma once

#include <Resources/Cursor.hpp>
#include <Resources/Icon.hpp>
#include <Stl/StlWrapper.hpp>

struct WindowConfig {
    static constexpr size_t MAX_RESOURCE_NAME_LENGTH = 100;

    std::array<CHAR, MAX_RESOURCE_NAME_LENGTH> title;
    int32_t height;
    int32_t width;

    // TODO: Turn these into pointers to ResourceManager objects.
    Icon appIcon_;
    Cursor mouseCursor_;
    bool showCursor_ = true;
    Icon smallAppIcon_;
    std::array<CHAR, MAX_RESOURCE_NAME_LENGTH> mainWindowClassName_;
};
