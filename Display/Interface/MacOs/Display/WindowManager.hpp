#pragma once

#include <Stl/StlWrapper.hpp>
#include <ErrorHandling/Result.hpp>

struct WindowConfig;
class Window;

class WindowManager {

public:
    static WindowManager& GetInstance();

public:
    Result Init();
    Result CreateNewWindow(const WindowConfig& config, Window** windowToReturn);
    //LRESULT ProcessMessage(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam);

private:
    WindowManager() = default;
    ~WindowManager();
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;
};

