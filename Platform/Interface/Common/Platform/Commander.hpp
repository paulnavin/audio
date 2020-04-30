#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Platform/CommandId.hpp>

class Minion;

// William Blazkowicz Jnr.
class Commander {

public:
    Commander() = default;
    virtual ~Commander() = default;

public:
    Result Init();

public:
    void Distribute(const CommandId& command);
    void DistributeMousePosition(const float& x, const float& y);
    void SendAppCommand(const CommandId& command);
    void SetAppCommandHandler(std::function<void(const CommandId& command)> handler);
    void Subscribe(const CommandId& command, Minion* receiver);
    void Unsubscribe(const CommandId& command, Minion* receiver);
    void SubscribeToMouseMove(Minion* receiver);
    void UnsubscribeFromMouseMove(Minion* receiver);

private:
    std::map<CommandId, std::set<Minion*> > receivers_;
    std::set<Minion*> mouseMoveReceviers_;
    std::function<void(const CommandId& command)> onAppCommand_;
};
