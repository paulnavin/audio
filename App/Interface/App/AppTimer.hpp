#pragma once

#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

class AppTimer {
public:
    AppTimer() = default;
    ~AppTimer() = default;
    Result Init();

public:
    const double GetTimeBetweenFramesInMs() const;
    const double GetTotalRunningTimeInS() const;

public:
    Result Start();
    Result Update();
    Result Pause();

private:
    int64_t currentTime_;
    int64_t lastFrameTime_;
    int64_t lastPausedTime_;
    int64_t startTime_;
    int64_t totalIdleTime_;

    LARGE_INTEGER cpuFrequency_;
    double msPerCpuCount_;
    double msBetweenFrames_;

    bool running_;
};