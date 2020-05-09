#pragma once

#include <Platform/CommandId.hpp>

static constexpr CommandId LeftButtonDown = 0;
static constexpr CommandId LeftButtonUp = LeftButtonDown + 1;

static constexpr CommandId NextCoreCommand = LeftButtonUp + 1;
