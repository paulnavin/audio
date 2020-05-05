#include <UserInput/KeyBinding.hpp>

KeyBinding::KeyBinding(const size_t& newKeyCode, const KeyState& newKeyState) {
    keyCode = newKeyCode;
    keyState = newKeyState;
}
