#pragma once

#include <App/AppUserInputCommands.hpp>
#include <UserInput/Command.hpp>

static constexpr Command::Id ShowSettings = NextAppCommand;
static constexpr Command::Id HideSettings = ShowSettings + 1;
static constexpr Command::Id SomeOtherCommand = HideSettings + 1;
