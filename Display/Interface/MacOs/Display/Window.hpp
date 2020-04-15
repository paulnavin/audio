#pragma once

#include <ErrorHandling/Result.hpp>

struct WindowConfig;
class WindowMessageHandler;

class Window {
public:
    Window() = default;
    ~Window() = default;

public:
    const float GetWidth() const;
    const float GetHeight() const;

public:
    Result Init();
    void Show();
    void Destroy();
    
    //LRESULT ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam);
    void SetWindowMessageHandler(WindowMessageHandler* newHandler);
    
    void UpdateSizes();

private:
    float height_;
    bool isMinimised_;
    bool isMaximised_;
    bool isResizing_;
    float width_;
    WindowMessageHandler* messageHandler_;
};
