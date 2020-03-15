#pragma once

#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

struct WindowConfig;
class WindowMessageHandler;

class Window {
public:
    Window() = default;
    ~Window() = default;

public:
    const HWND GetHandle() const;

    const float GetWidth() const;
    const float GetHeight() const;

public:
    Result Init(const WNDCLASSEXW& wcex, const WindowConfig& config);
    void Show();
    LRESULT ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam);
    void SetWindowMessageHandler(WindowMessageHandler* newHandler);
    void Destroy();

private:
    void HandleSizeMessage(const WPARAM& wParam);
    LRESULT DisableAnnoyingMenuBeepingSound();
    void UpdateSizes();

private:
    HINSTANCE appInstance_;
    RECT clientArea_;
    float height_;
    bool isMinimised_;
    bool isMaximised_;
    bool isResizing_;
    float width_;
    HWND windowHandle_;
    RECT windowArea_;
    WindowMessageHandler* messageHandler_;
};
