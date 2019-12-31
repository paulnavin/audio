#pragma once

#include <cstdint>

#include "KeyState.hpp"

struct KeyBinding {
public:
    KeyBinding(const uint16_t& newKeyCode, const KeyState& newKeyState);

public:
    uint16_t keyCode;
    KeyState keyState;
};
