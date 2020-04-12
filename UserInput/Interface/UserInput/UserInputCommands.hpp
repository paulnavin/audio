#pragma once

#include <UserInput/Command.hpp>

static constexpr Command::Id LeftButtonDown = 0;
static constexpr Command::Id LeftButtonUp = LeftButtonDown + 1;

static constexpr Command::Id NextCoreCommand = LeftButtonUp + 1;
