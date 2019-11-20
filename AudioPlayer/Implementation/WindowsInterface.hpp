#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files
#pragma warning( disable : 5039)	// disable pointer or reference to potentially throwing function passed to extern C function warning
#pragma warning( disable : 4820)    // Struct padding warning
#pragma warning( disable : 4365)    // Conversion from long to stuff warning

#include <windows.h>

#include "Resource.h"
