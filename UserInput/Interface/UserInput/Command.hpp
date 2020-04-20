#pragma once

#include <Platform/Stl.hpp>

#include "KeyBinding.hpp"

struct Command {
public:
    using Id = uint16_t;
    using KeyBindingVector = std::vector<KeyBinding>;

public:
    Command(const Id& newId, const std::string& newName, const KeyBindingVector& newBindings);

public:
    Id id;
    std::string name;
    KeyBindingVector keyCombo;
};
