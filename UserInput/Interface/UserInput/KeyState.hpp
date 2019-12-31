#pragma once

#include <cstdint>

enum class KeyState : uint16_t {
    JustPressed,
    StillPressed,
    JustReleased,
    StillReleased,
};
