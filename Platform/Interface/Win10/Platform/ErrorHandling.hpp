#pragma once

#include <Platform/Result.hpp>

#define ReturnIfHrError(X, MESSAGE) \
    { \
        HRESULT hr = X; \
        if (FAILED(hr)) { \
            result.AppendError(MESSAGE); \
            return result; \
        } \
    }
