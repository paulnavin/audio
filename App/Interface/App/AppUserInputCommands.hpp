#pragma once

#include <UserInput/Command.hpp>

static constexpr Command::Id Quit = 0;
static constexpr Command::Id ToggleFps = Quit + 1;
static constexpr Command::Id ToggleMousePosition= ToggleFps + 1;
static constexpr Command::Id ToggleScene = ToggleMousePosition + 1;
static constexpr Command::Id RecreateModels = ToggleScene + 1;
static constexpr Command::Id MouseClicked = RecreateModels + 1;
static constexpr Command::Id ToggleFullScreen = MouseClicked + 1;
static constexpr Command::Id NextDisplayConfig = ToggleFullScreen + 1;
static constexpr Command::Id PreviousDisplayConfig = NextDisplayConfig + 1;
static constexpr Command::Id ResetDisplayConfig = PreviousDisplayConfig + 1;

static constexpr Command::Id NextAppCommand = ResetDisplayConfig + 1;
