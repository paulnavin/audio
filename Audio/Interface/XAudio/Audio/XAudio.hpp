#pragma once

#pragma warning(push)
#pragma warning( disable : 4514)    //  Inline function removed.
#pragma warning( disable : 4668)    //  Something not defined as a preprocessor macro, assuming 0
#pragma warning( disable : 5039)	//  disable pointer or reference to potentially throwing function passed to extern C function warning

// For audio playing/mixing. 
#include <xaudio2.h>

// For Windows COM stuff.
#include <wrl/client.h>

// Windows Media Foundation for reading/writing audio files.
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

#pragma warning(pop)    // Turn back on all warnings.