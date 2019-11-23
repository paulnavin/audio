#pragma once

#include "WindowsInterface.hpp"

#pragma warning(push)
#pragma warning( disable : 4577)
#include <cstdint>
#pragma warning(pop)

#include "Result.hpp"

class AppTimer {
public:
    AppTimer() = default;
    ~AppTimer() = default;
    Result Init();

public:
    const double GetTimeBetweenFramesInS() const;
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
    double secondsPerCpuCount_;
    double timeBetweenFrames_;

#pragma warning(push)
#pragma warning(disable : 4820) // Padding after running_.
    bool running_;
};
#pragma warning(pop)
