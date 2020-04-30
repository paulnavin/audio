#include <UserInput/Command.hpp>

Command::Command(const CommandId& newId, const std::string& newName, const KeyBindingVector& newBindings)
    : id(newId)
    , name(newName)
    , keyCombo(newBindings) {}
