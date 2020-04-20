#pragma once

class WindowMessageHandler {
public:
    virtual void OnActivate() = 0;
    virtual void OnClose() = 0;
    virtual void OnMinimise() = 0;
    virtual void OnMaximise() = 0;
    virtual void OnRestore() = 0;
    virtual void OnStartSizeOrMove() = 0;
    virtual void OnFinishSizeOrMove() = 0;

public:
    WindowMessageHandler() = default;
    virtual ~WindowMessageHandler() = default;
};
