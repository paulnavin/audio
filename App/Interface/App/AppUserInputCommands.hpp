#pragma once

#include <UserInput/Command.hpp>

static constexpr Command::Id Quit = 0;
static constexpr Command::Id ToggleDebugInfo = Quit + 1;
static constexpr Command::Id ToggleScene = ToggleDebugInfo + 1;
static constexpr Command::Id RecreateModels = ToggleScene + 1;
static constexpr Command::Id LeftButtonDown = RecreateModels + 1;
static constexpr Command::Id LeftButtonUp = LeftButtonDown + 1;
static constexpr Command::Id ToggleFullScreen = LeftButtonUp + 1;
static constexpr Command::Id NextDisplayConfig = ToggleFullScreen + 1;
static constexpr Command::Id PreviousDisplayConfig = NextDisplayConfig + 1;
static constexpr Command::Id ResetDisplayConfig = PreviousDisplayConfig + 1;

static constexpr Command::Id NextAppCommand = ResetDisplayConfig + 1;
