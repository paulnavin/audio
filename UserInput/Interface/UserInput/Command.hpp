#pragma once

#include <Utility/StlWrapper.hpp>

#include "KeyBinding.hpp"

struct Command {
public:
    using Id = uint16_t;
    using KeyBindingVector = std::vector<KeyBinding>;

public:
    Command(const std::string& newName, const KeyBindingVector& newBindings);

public:
    std::string name;
    KeyBindingVector keyCombo;
};
