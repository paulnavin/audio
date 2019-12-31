#pragma once

#include "Command.hpp"

#include <Utility/StlWrapper.hpp>

class InputManager {
public:
    InputManager();
    ~InputManager();

public:
    const KeyState GetStateForKey(const unsigned int keyCode) const;
    const bool IsKeyPressed(const uint16_t& keyCode) const;

public:
    void RefreshKeyboardState();
    void Update();

private:
    using CommandMap = std::map<Command::Id, Command*>;
    static constexpr size_t KEY_COUNT = 256;
private:
    CommandMap activeKeyMap_;
    CommandMap coreKeyMap_;

    std::array<bool, KEY_COUNT> keyboardStateCurrent_;
    std::array<bool, KEY_COUNT> keyboardStatePrevious_;
};
