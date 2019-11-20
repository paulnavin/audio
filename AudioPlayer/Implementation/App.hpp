#pragma once

#include "WindowsInterface.hpp"

#include "Result.hpp"

class Window;

class App {
public:
    App() = default;
    ~App() = default;

public:
    Result Init(const HINSTANCE& appInstance);
    void Run();
    void ShutDown();

private:
    HINSTANCE appInstance_;
    HACCEL acceleratorTable_;
    Window* mainWindow_;
};
