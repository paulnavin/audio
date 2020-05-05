#pragma once

#include <Platform/ErrorHandling.hpp>

struct AppInstance;
struct WindowConfig;
class Window;

class WindowManager {

public:
    static WindowManager& GetInstance();

public:
    Result Init(const AppInstance& appInstance, const WindowConfig& windowConfig);
    Window* GetWindow();

private:
    WindowManager() = default;
    ~WindowManager();
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;

private:
    // Only support one window for now.
    Window* window_;
};

