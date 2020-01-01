#pragma once

#include "Command.hpp"

static constexpr Command::Id Quit = 0;
static constexpr Command::Id ToggleFps = Quit + 1;
static constexpr Command::Id ToggleMousePosition= ToggleFps + 1;
static constexpr Command::Id FirstAppCommand = ToggleMousePosition + 1;
