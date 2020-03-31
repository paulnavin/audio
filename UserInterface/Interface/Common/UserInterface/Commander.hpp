#pragma once

#include <ErrorHandling/Result.hpp>
#include <UserInput/Command.hpp>

class Element;

class Commander {

public:
    Commander() = default;
    virtual ~Commander() = default;

public:
    Result Init();

public:
    void RegisterForCommand(const Command::Id& command, Element* receiver);

private:
    std::map<Command::Id, std::vector<Element*> > receivers_;
};
