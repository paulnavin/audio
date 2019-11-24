#pragma once

#include "WindowsInterface.hpp"

#include "Direct3dController.hpp"
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
    Result Render(const double& dt);
    void Destroy();

private:
    void HandleKeyUp(const WPARAM& wParam);

private:
    HINSTANCE appInstance_;
    Direct3dController direct3dController_;
    HWND windowHandle_;
};
