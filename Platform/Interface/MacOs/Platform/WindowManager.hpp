#pragma once

#include <Platform/Stl.hpp>
#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

struct AppInstance;
struct WindowConfig;
class Window;

class WindowManager {

public:
    static WindowManager& GetInstance();

public:
    Result Init(const AppInstance& appInstance, const WindowConfig& windowConfig);
    Result CreateNewWindow(const WindowConfig& config, Window** windowToReturn);

private:
    WindowManager() = default;
    ~WindowManager();
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;
};

