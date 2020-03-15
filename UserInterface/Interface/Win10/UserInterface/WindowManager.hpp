#pragma once

#include <UserInterface/Window.hpp>
#include <Stl/StlWrapper.hpp>
#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

struct WindowConfig;

class WindowManager {

public:
    static WindowManager& GetInstance();

public:
    Result Init(const HINSTANCE& appInstance, const WindowConfig& windowConfig);
    Result CreateNewWindow(const WindowConfig& config, Window** windowToReturn);
    LRESULT ProcessMessage(const HWND& hWnd, const UINT& message, const WPARAM& wParam, const LPARAM& lParam);

private:
    WindowManager() = default;
    ~WindowManager();
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;

private:
    #pragma warning( disable : 4625) // Warning about Window having an implicitly deleted copy constructor.
    #pragma warning( disable : 5027) // Warning about Window having an implicitly deleted move constructor.
    #pragma warning( disable : 4626) // Warning about Window having an implicitly deleted assignment operator.
    #pragma warning( disable : 4571) // Something about catch(...) semantics.
    using HandleToWindowMap = std::map<HWND, Window*>;
    HandleToWindowMap windows_;

    WNDCLASSEX wcex_;
};

