#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Platform/WindowsInterface.hpp>

class Icon {
public:
    Icon() = default;
    ~Icon() = default;

public:
    const HICON GetHandle() const;

public:
    Result Init(const HINSTANCE& appInstance, const LPCSTR& iconName);

private:
    HICON handle_;
};
