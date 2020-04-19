#pragma once

#include <Stl/StlWrapper.hpp>

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


#define ReturnIfHrError(X, MESSAGE) \
    { \
        HRESULT hr = X; \
        if (result.HasErrors()) { \
            result.AppendError(MESSAGE); \
            return result; \
        } \
    }

#define ReturnIfResultError(X, MESSAGE) \
    { \
        result = X; \
        if (result.HasErrors()) { \
            result.AppendError(MESSAGE); \
            return result; \
        } \
    }
