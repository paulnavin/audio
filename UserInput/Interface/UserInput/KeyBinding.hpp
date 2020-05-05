#pragma once

#include "KeyState.hpp"

struct KeyBinding {
public:
    KeyBinding(const size_t& newKeyCode, const KeyState& newKeyState);

public:
    size_t keyCode;
    KeyState keyState;
};
