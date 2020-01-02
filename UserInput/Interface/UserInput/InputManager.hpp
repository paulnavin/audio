#pragma once

#include "Command.hpp"

#include <Utility/StlWrapper.hpp>

class Window;

class InputManager {
public:
    using CommandMap = std::map<Command::Id, Command*>;

public:
    InputManager();
    ~InputManager();

public:
    const CommandMap* GetActiveKeyMap() const;
    const KeyState GetStateForKey(const unsigned int keyCode) const;
    const int32_t GetMouseXPos() const;
    const int32_t GetMouseYPos() const;
    const bool IsKeyPressed(const uint16_t& keyCode) const;

public:
    void RefreshKeyboardState();
    void RefreshMouseState(const Window& targetWindow);
    void Update(const Window& targetWindow);

private:
    static constexpr size_t KEY_COUNT = 256;

private:
    CommandMap activeKeyMap_;
    CommandMap coreKeyMap_;

    std::array<bool, KEY_COUNT> keyboardStateCurrent_;
    std::array<bool, KEY_COUNT> keyboardStatePrevious_;

    int32_t mouseXPos_;
    int32_t mouseYPos_;
};
