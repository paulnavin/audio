#pragma once

#include <Utility/Result.hpp>
#include <Utility/WindowsInterface.hpp>

class Icon {
public:
    Icon() = default;
    ~Icon() = default;

public:
    const HICON GetHandle() const;

public:
    Result Init(const HINSTANCE& appInstance, const LPCWSTR& iconName);

private:
    HICON handle_;
};
