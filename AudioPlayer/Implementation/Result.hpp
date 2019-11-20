#pragma once

#pragma warning(push)
#pragma warning( disable : 4514)    // Inline function removed.
#pragma warning( disable : 4625) // Warning about Window having an implicitly deleted copy constructor.
#pragma warning( disable : 5026) // Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 5027) // Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 4626) // Warning about Window having an implicitly deleted assignment operator.
#pragma warning( disable : 4571) // Something about catch(...) semantics.
#pragma warning( disable : 5039)	// disable pointer or reference to potentially throwing function passed to extern C function warning
#pragma warning( disable : 4820)    // Struct padding warning
#pragma warning( disable : 4365)    // Conversion from long to stuff warning
#pragma warning( disable : 4774)    // 'sprintf_s' : format string expected in argument 3 is not a string literal
#pragma warning( disable : 4710)    //  function not inlined
#pragma warning( disable : 4577)    //  noexcept
#pragma warning( disable : 4530)    //  C++ exception handler used, but unwind semantics are not enabled
#include <string>
#include <vector>
#pragma warning(pop)    // Turn back on all warnings.

class Result {
public:
    using ErrorList = std::vector<std::string>;

public:
    // TODO: Define move constructor/assignment?
    Result() = default;
    ~Result() = default;

public:
    const bool HasErrors() const;
    const bool IsOkay() const;
    const std::string Errors() const;

public:
    void AppendError(const char* newError);

private:
    ErrorList errors_;
};
