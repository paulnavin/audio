#include <UserInterface/Commander.hpp>

#include <Platform/WindowsInterface.hpp>
#include <UserInterface/Element.hpp>

Result Commander::Init() {
    return Result{};
}

void Commander::Distribute(const Command::Id& command) {
    for (Element* element : receivers_[command]) {
        if (element->IsEnabled() == true) {
            element->HandleCommand(command);
        }
    }
}

void Commander::DistributeMousePosition(const float& x, const float& y) {
    for (Element* element : mouseMoveReceviers_) {
        if (element->IsEnabled() == true) {
            element->HandleMouseMove(x, y);
        }
    }
}

void Commander::Subscribe(const Command::Id& command, Element* receiver) {
    receivers_[command].insert(receiver);
}

void Commander::Unsubscribe(const Command::Id& command, Element* receiver) {
    receivers_[command].erase(receiver);
}

void Commander::SubscribeToMouseMove(Element* receiver) {
    mouseMoveReceviers_.push_back(receiver);
}