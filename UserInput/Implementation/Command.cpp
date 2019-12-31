#include <UserInput/Command.hpp>

Command::Command(const std::string& newName, const KeyBindingVector& newBindings) {
    name = newName;
    keyCombo = newBindings;
}
