#pragma once

#include <ErrorHandling/Result.hpp>
#include <UserInput/Command.hpp>

class Element;

// William Blazkowicz Jnr.
class Commander {

public:
    Commander() = default;
    virtual ~Commander() = default;

public:
    Result Init();

public:
    void Distribute(const Command::Id& command);
    void DistributeMousePosition(const float& x, const float& y);
    void SendAppCommand(const Command::Id& command);
    void SetAppCommandHandler(std::function<void(const Command::Id& command)> handler);
    void Subscribe(const Command::Id& command, Element* receiver);
    void Unsubscribe(const Command::Id& command, Element* receiver);
    void SubscribeToMouseMove(Element* receiver);
    void UnsubscribeFromMouseMove(Element* receiver);

private:
    std::map<Command::Id, std::set<Element*> > receivers_;
    std::set<Element*> mouseMoveReceviers_;
    std::function<void(const Command::Id& command)> onAppCommand_;
};
