#pragma once

#include <Platform/CommandId.hpp>
#include <Platform/Stl.hpp>

#include "KeyBinding.hpp"

struct Command {
public:
    using KeyBindingVector = std::vector<KeyBinding>;

public:
    Command(const CommandId& newId, const std::string& newName, const KeyBindingVector& newBindings);

public:
    CommandId id;
    std::string name;
    KeyBindingVector keyCombo;
};
