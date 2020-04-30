#pragma once

#include <Platform/CommandId.hpp>

class Minion {
public:
    Minion() = default;
    virtual ~Minion() = default;

public:
    virtual const bool IsEnabled() const = 0;

    virtual void HandleCommand(const CommandId& /*command*/) {};

    virtual void HandleMouseMove(const float& /*x*/, const float& /*y*/) {};
};