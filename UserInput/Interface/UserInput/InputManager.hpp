#pragma once

#include "Command.hpp"

#include <Platform/ErrorHandling.hpp>
#include <Platform/Stl.hpp>

class Window;

// Retrieves state of system, storing the result as Commands.
// Note: Doesn't notify anything, just stores the state.
class InputManager {
public:
    using CommandMap = std::map<CommandId, Command*>;
    using CommandQueue = std::deque<CommandId>;

public:
    InputManager() = default;
    ~InputManager();

public:
    const CommandMap* GetActiveKeyMap() const;
    const KeyState GetStateForKey(const unsigned int keyCode) const;
    const int32_t GetMouseXPos() const;
    const int32_t GetMouseYPos() const;
    const bool IsKeyPressed(const uint16_t& keyCode) const;

public:
    void ActivateCommand(const CommandId& command);
    void AddCoreCommand(Command* command);
    Result Init(Window* targetWindow);
    void RefreshKeyboardState();
    void RefreshMouseState();
    void Update();

private:
    static constexpr size_t KEY_COUNT = 256;

private:
    CommandMap activeKeyMap_;
    CommandMap coreKeyMap_;
    CommandQueue appCommandQueue_;

    std::array<bool, KEY_COUNT> keyboardStateCurrent_;
    std::array<bool, KEY_COUNT> keyboardStatePrevious_;

    int32_t mouseXPos_;
    int32_t mouseYPos_;

    Window* targetWindow_;
};
