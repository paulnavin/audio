#include <Platform/Commander.hpp>

#include <Platform/WindowsInterface.hpp>
#include <Platform/Minion.hpp>

Result Commander::Init() {
    return Result{};
}

void Commander::Distribute(const CommandId& command) {
    for (Minion* element : receivers_[command]) {
        if (element->IsEnabled() == true) {
            element->HandleCommand(command);
        }
    }
}

void Commander::DistributeMousePosition(const float& x, const float& y) {
    for (Minion* element : mouseMoveReceviers_) {
        if (element->IsEnabled() == true) {
            element->HandleMouseMove(x, y);
        }
    }
}

void Commander::SendAppCommand(const CommandId& command) {
    onAppCommand_(command);
}

void Commander::SetAppCommandHandler(std::function<void(const CommandId& command)> handler) {
    onAppCommand_ = handler;
}

void Commander::Subscribe(const CommandId& command, Minion* receiver) {
    receivers_[command].insert(receiver);
}

void Commander::Unsubscribe(const CommandId& command, Minion* receiver) {
    receivers_[command].erase(receiver);
}

void Commander::SubscribeToMouseMove(Minion* receiver) {
    mouseMoveReceviers_.insert(receiver);
}

void Commander::UnsubscribeFromMouseMove(Minion* receiver) {
    mouseMoveReceviers_.erase(receiver);
}