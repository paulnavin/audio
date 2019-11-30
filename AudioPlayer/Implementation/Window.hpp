#pragma once

#include "WindowsInterface.hpp"

#include "Result.hpp"

struct WindowConfig;

class Window {
public:
    Window() = default;
    ~Window() = default;

public:
    const HWND GetHandle() const;

public:
    Result Init(const WNDCLASSEXW& wcex, const WindowConfig& config);
    void Show();
    LRESULT ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam);
    void Destroy();

private:
    void HandleKeyUp(const WPARAM& wParam);

private:
    HINSTANCE appInstance_;
    HWND windowHandle_;
};
