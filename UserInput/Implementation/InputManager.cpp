#include <UserInput/InputManager.hpp>

#include <UserInput/CoreCommands.hpp>
#include <UserInput/KeyBinding.hpp>
#include <UserInput/KeyState.hpp>
#include <UserInterface/Window.hpp>
#include <Utility/WindowsInterface.hpp>

InputManager::InputManager() {
    std::vector<KeyBinding> toggleFpsBindings;
    toggleFpsBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding('F', KeyState::JustPressed));
    coreKeyMap_[ToggleFps] = new Command("Toggle FPS", toggleFpsBindings);

    std::vector<KeyBinding> toggleModelBindings;
    toggleModelBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    toggleModelBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    toggleModelBindings.push_back(KeyBinding('2', KeyState::JustPressed));
    coreKeyMap_[Toggle2dModel] = new Command("Toggle 2D Model", toggleModelBindings);

    std::vector<KeyBinding> recreateModelBindings;
    recreateModelBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    recreateModelBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    recreateModelBindings.push_back(KeyBinding('R', KeyState::JustPressed));
    coreKeyMap_[RecreateModel] = new Command("Recreate Models", recreateModelBindings);


    std::vector<KeyBinding> toggleMousePositionBindings;
    toggleMousePositionBindings.push_back(KeyBinding(VK_RBUTTON, KeyState::JustReleased));
    coreKeyMap_[ToggleMousePosition] = new Command("Toggle Mouse Position", toggleMousePositionBindings);

    std::vector<KeyBinding> mouseClickedBindings;
    mouseClickedBindings.push_back(KeyBinding(VK_LBUTTON, KeyState::JustReleased));
    coreKeyMap_[MouseClicked] = new Command("Left Click", mouseClickedBindings);

    std::vector<KeyBinding> quitBindings;
    quitBindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    coreKeyMap_[Quit] = new Command("Quit", quitBindings);
}

InputManager::~InputManager() {
    for (auto command : coreKeyMap_) {
        delete command.second;
    }
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

void InputManager::RefreshKeyboardState() {
    keyboardStatePrevious_ = keyboardStateCurrent_;

    // read the current keyboard state
    for (uint16_t i = 0; i < KEY_COUNT; ++i) {
        keyboardStateCurrent_[i] = IsKeyPressed(i);
    }
}

void InputManager::RefreshMouseState(const Window& targetWindow) {
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    ScreenToClient(targetWindow.GetHandle(), &mousePoint);
    mouseXPos_ = mousePoint.x;
    mouseYPos_ = mousePoint.y;
}

void InputManager::Update(const Window& targetWindow) {
    RefreshKeyboardState();
    RefreshMouseState(targetWindow);

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
