#pragma once

#include <ErrorHandling/Result.hpp>

class Icon {
public:
    Icon() = default;
    ~Icon() = default;

public:
    Result Init(const HINSTANCE& appInstance, const LPCSTR& iconName);
};
