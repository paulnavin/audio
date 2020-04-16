#pragma once

#include <UserInput/UserInputCommands.hpp>

static constexpr Command::Id Quit = NextCoreCommand;
static constexpr Command::Id MouseMove = Quit + 1;
static constexpr Command::Id ToggleDebugInfo = MouseMove + 1;
static constexpr Command::Id ToggleScene = ToggleDebugInfo + 1;
static constexpr Command::Id RecreateModels = ToggleScene + 1;
static constexpr Command::Id ToggleFullScreen = RecreateModels + 1;
static constexpr Command::Id NextDisplayConfig = ToggleFullScreen + 1;
static constexpr Command::Id PreviousDisplayConfig = NextDisplayConfig + 1;
static constexpr Command::Id ResetDisplayConfig = PreviousDisplayConfig + 1;

static constexpr Command::Id NextAppCommand = ResetDisplayConfig + 1;
