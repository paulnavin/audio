#include <UserInput/InputManager.hpp>

#include <UserInput/KeyBinding.hpp>
#include <UserInput/KeyState.hpp>
#include <Display/Window.hpp>
#include <Platform/WindowsInterface.hpp>

InputManager::~InputManager() {
    for (auto command : coreKeyMap_) {
        delete command.second;
    }
}

Result InputManager::Init(Window* targetWindow) {
    Result initResult{};

    targetWindow_ = targetWindow;

    return initResult;
}

const InputManager::CommandMap* InputManager::GetActiveKeyMap() const {
    return &activeKeyMap_;
}

const int32_t InputManager::GetMouseXPos() const {
    return mouseXPos_;
}

const int32_t InputManager::GetMouseYPos() const {
    return mouseYPos_;
}

const KeyState InputManager::GetStateForKey(const unsigned int keyCode) const {
    if (keyboardStatePrevious_[keyCode] == true) {
        if (keyboardStateCurrent_[keyCode] == true) {
            return KeyState::StillPressed;
        } else {
            return KeyState::JustReleased;
        }
    } else {
        if (keyboardStateCurrent_[keyCode] == true) {
            return KeyState::JustPressed;
        } else {
            return KeyState::StillReleased;
        }
    }
}

const bool InputManager::IsKeyPressed(const uint16_t& keyCode) const {
    return (GetAsyncKeyState(keyCode) & 0x8000) ? 1 : 0;
}

void InputManager::AddCommand(Command* command) {
    coreKeyMap_[command->id] = command;
}

void InputManager::RefreshKeyboardState() {
    keyboardStatePrevious_ = keyboardStateCurrent_;

    // read the current keyboard state
    for (uint16_t i = 0; i < KEY_COUNT; ++i) {
        keyboardStateCurrent_[i] = IsKeyPressed(i);
    }
}

void InputManager::RefreshMouseState() {
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    ScreenToClient(targetWindow_->GetHandle(), &mousePoint);
    mouseXPos_ = mousePoint.x;
    mouseYPos_ = mousePoint.y;
}

void InputManager::Update() {
    RefreshKeyboardState();
    RefreshMouseState();

    bool isActive = false;
    activeKeyMap_.clear();

    // Go through all the possible bindings to see if they're active.
    for (auto command : coreKeyMap_) {
        isActive = true;
        // For each binding, check whether all the key combinations are active.
        for (auto binding : command.second->keyCombo) {
            if (GetStateForKey(binding.keyCode) != binding.keyState) {
                isActive = false;
                break;
            }
        }
        if (isActive == true) {
            activeKeyMap_.insert(std::pair<Command::Id, Command*>(command.first, command.second));
        }
    }
}
