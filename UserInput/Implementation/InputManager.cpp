#include <UserInput/InputManager.hpp>

#include <UserInput/CoreCommands.hpp>
#include <UserInput/KeyBinding.hpp>
#include <UserInput/KeyState.hpp>
#include <Utility/WindowsInterface.hpp>

InputManager::InputManager() {
    std::vector<KeyBinding> toggleFpsBindings;
    toggleFpsBindings.push_back(KeyBinding(VK_SHIFT, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding(VK_CONTROL, KeyState::StillPressed));
    toggleFpsBindings.push_back(KeyBinding('F', KeyState::JustPressed));
    coreKeyMap_[ToggleFps] = new Command("Toggle FPS", toggleFpsBindings);

    std::vector<KeyBinding> quitBindings;
    quitBindings.push_back(KeyBinding(VK_ESCAPE, KeyState::JustPressed));
    coreKeyMap_[Quit] = new Command("Quit", quitBindings);
}

InputManager::~InputManager() {
    CommandMap::iterator commandFinder = coreKeyMap_.begin();
    CommandMap::iterator commandEnd = coreKeyMap_.end();
    while (commandFinder != commandEnd) {
        delete commandFinder->second;

        // Loop incrementer;
        ++commandFinder;
    }
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

void InputManager::Update() {
    RefreshKeyboardState();

    bool isActive = false;
    activeKeyMap_.clear();

    // Go through all the possible bindings to see if they're active.
    for (auto x : coreKeyMap_) {
        isActive = true;
        // For each binding, check whether all the key combinations are active.
        for (auto y : x.second->keyCombo) {
            if (GetStateForKey(y.keyCode) != y.keyState) {
                isActive = false;
                break;
            }
        }
        if (isActive == true) {
            activeKeyMap_.insert(std::pair<Command::Id, Command*>(x.first, x.second));
        }
    }
}
