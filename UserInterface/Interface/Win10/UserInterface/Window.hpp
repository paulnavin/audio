#pragma once

#include <Utility/Result.hpp>
#include <Utility/WindowsInterface.hpp>

struct WindowConfig;

class Window {
public:
    Window() = default;
    ~Window() = default;

public:
    const HWND GetHandle() const;
    const float GetXPosition() const;
    const float GetYPosition() const;

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
    RECT windowRectangle_;
};
