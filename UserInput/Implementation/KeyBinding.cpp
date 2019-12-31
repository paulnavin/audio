#include <UserInput/KeyBinding.hpp>

KeyBinding::KeyBinding(const uint16_t& newKeyCode, const KeyState& newKeyState) {
    keyCode = newKeyCode;
    keyState = newKeyState;
}
