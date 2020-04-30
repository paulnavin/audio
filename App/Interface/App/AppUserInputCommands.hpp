#pragma once

#include <UserInput/UserInputCommands.hpp>

static constexpr CommandId Quit = NextCoreCommand;
static constexpr CommandId MouseMove = Quit + 1;
static constexpr CommandId ToggleDebugInfo = MouseMove + 1;
static constexpr CommandId ToggleScene = ToggleDebugInfo + 1;
static constexpr CommandId RecreateModels = ToggleScene + 1;
static constexpr CommandId ToggleFullScreen = RecreateModels + 1;
static constexpr CommandId NextDisplayConfig = ToggleFullScreen + 1;
static constexpr CommandId PreviousDisplayConfig = NextDisplayConfig + 1;
static constexpr CommandId ResetDisplayConfig = PreviousDisplayConfig + 1;

static constexpr CommandId NextAppCommand = ResetDisplayConfig + 1;
