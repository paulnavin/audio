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
    Result Init(const WindowConfig& config);
    void Show();
    void Destroy();

    void SetWindowMessageHandler(WindowMessageHandler* newHandler);

    void UpdateSizes();

private:
    WindowMessageHandler* messageHandler_;
};
