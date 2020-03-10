#pragma once

#include <App/AppUserInputCommands.hpp>
#include <UserInput/Command.hpp>

static constexpr Command::Id SomeNewCommand = NextAppCommand;
static constexpr Command::Id SomeOtherCommand = SomeNewCommand + 1;
