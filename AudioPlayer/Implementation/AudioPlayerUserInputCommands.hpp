#pragma once

#include <App/AppUserInputCommands.hpp>
#include <UserInput/Command.hpp>

static constexpr CommandId ShowSettings = NextAppCommand;
static constexpr CommandId HideSettings = ShowSettings + 1;
static constexpr CommandId SomeOtherCommand = HideSettings + 1;
