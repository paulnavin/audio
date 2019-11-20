#pragma once

#include "WindowsInterface.hpp"

#include "Result.hpp"

class Window {
public:
    Window() = default;
    ~Window() = default;

public:
    const HWND GetHandle() const;

public:
    Result Init(const WNDCLASSEXW& wcex);
    void Show();
    LRESULT ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam);
    void Destroy();

private:
    HINSTANCE appInstance_;
    HWND windowHandle_;
};
