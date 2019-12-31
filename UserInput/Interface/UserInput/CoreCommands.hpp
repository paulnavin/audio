#pragma once

#include "Command.hpp"

static constexpr Command::Id Quit = 0;
static constexpr Command::Id ToggleFps = Quit + 1;
static constexpr Command::Id FirstAppCommand = ToggleFps + 1;
