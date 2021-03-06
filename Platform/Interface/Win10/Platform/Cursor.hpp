#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Platform/WindowsInterface.hpp>

class Cursor {
public:
    Cursor() = default;
    ~Cursor() = default;

public:
    const HCURSOR GetHandle() const;

public:
    Result Init(const HINSTANCE& appInstance, const LPCSTR& cursorName);

private:
    HCURSOR handle_;
};
