#pragma once

class Result {
public:
    // TODO: Define move constructor/assignment?
    Result() = default;
    ~Result() = default;

public:
    const bool HasErrors() const;
    const bool IsOkay() const;
    const char* Errors() const;

public:
    void AppendError(const char* newError);

private:
    static const size_t MAX_STRING_COUNT = 10;
    static const size_t MAX_STRING_LENGTH = 100;
    char finalError_[MAX_STRING_COUNT * MAX_STRING_LENGTH];
    size_t errorCount_ = 0;
};

#define ReturnIfResultError(X, MESSAGE) \
    { \
        result = X; \
        if (result.HasErrors()) { \
            result.AppendError(MESSAGE); \
            return result; \
        } \
    }
