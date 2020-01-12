#pragma once

#include "Command.hpp"

static constexpr Command::Id Quit = 0;
static constexpr Command::Id ToggleFps = Quit + 1;
static constexpr Command::Id ToggleMousePosition= ToggleFps + 1;
static constexpr Command::Id Toggle2dModel = ToggleMousePosition + 1;
static constexpr Command::Id RecreateModel = Toggle2dModel + 1;
static constexpr Command::Id MouseClicked = RecreateModel + 1;
static constexpr Command::Id FirstAppCommand = MouseClicked + 1;
