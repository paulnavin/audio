#pragma once

#include <Platform/WindowsInterface.hpp>

struct AppInstance {
    AppInstance();
    ~AppInstance() = default;

    HINSTANCE appHandle;
};
