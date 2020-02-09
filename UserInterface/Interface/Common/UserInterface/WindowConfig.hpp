#pragma once

#include <UserInterface/Cursor.hpp>
#include <UserInterface/Icon.hpp>
#include <Utility/StlWrapper.hpp>

struct WindowConfig {
    static constexpr size_t MAX_RESOURCE_NAME_LENGTH = 100;

    std::array<WCHAR, MAX_RESOURCE_NAME_LENGTH> title;
    int32_t height;
    int32_t width;
    Icon appIcon_;
    Cursor mouseCursor_;
    Icon smallAppIcon_;
    std::array<WCHAR, MAX_RESOURCE_NAME_LENGTH> mainWindowClassName_;
};
