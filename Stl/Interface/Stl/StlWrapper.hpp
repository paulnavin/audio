#pragma once

#pragma warning(push)
#pragma warning( disable : 4514)    //  Inline function removed.
#pragma warning( disable : 4625)    //  Warning about Window having an implicitly deleted copy constructor.
#pragma warning( disable : 5026)    //  Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 5027)    //  Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 4626)    //  Warning about Window having an implicitly deleted assignment operator.
#pragma warning( disable : 4571)    //  Something about catch(...) semantics.
#pragma warning( disable : 5039)	//  disable pointer or reference to potentially throwing function passed to extern C function warning
#pragma warning( disable : 4820)    //  Struct padding warning
#pragma warning( disable : 4365)    //  Conversion from long to stuff warning
#pragma warning( disable : 4774)    //  'sprintf_s' : format string expected in argument 3 is not a string literal
#pragma warning( disable : 4710)    //  function not inlined
#pragma warning( disable : 4577)    //  noexcept
#pragma warning( disable : 4530)    //  C++ exception handler used, but unwind semantics are not enabled
#pragma warning( disable : 4061)    //  enumerator 'D3D_SRV_DIMENSION_UNKNOWN' in switch of enum 'D3D_SRV_DIMENSION' is not explicitly handled by a case label
#pragma warning( disable : 4668)    //  '_WIN32_WINNT_WIN10_RS2' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'

#include <array>
#include <cstdint>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#pragma warning(pop)    // Turn back on all warnings.