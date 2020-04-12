#pragma once

#include <App/AppUserInputCommands.hpp>
#include <UserInput/Command.hpp>

static constexpr Command::Id ShowSettings = NextAppCommand;
static constexpr Command::Id SomeOtherCommand = ShowSettings + 1;
