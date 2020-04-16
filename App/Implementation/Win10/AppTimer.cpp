#include <App/AppTimer.hpp>

#include <Platform/WindowsInterface.hpp>

Result AppTimer::Init() {
    Result initResult;

    if (running_ == true) {
        initResult.AppendError("AppTimer::Init() : Timer is already running, can't Init() it.");
        return initResult;
    }

    // Gives back frequency in counts per second.
    LARGE_INTEGER frequencyInput;
    if (QueryPerformanceFrequency(&frequencyInput) == FALSE) {
        initResult.AppendError("AppTimer::Init() : Could not initialise timer.");
        return initResult;
    }
    cpuFrequency_ = frequencyInput.QuadPart;

    // Get the frequency in counts per ms.
    double frequency = static_cast<double>(cpuFrequency_ / 1000);
    msPerCpuCount_ = 1 / frequency;
    currentTime_ = 0;
    lastFrameTime_ = 0;
    lastPausedTime_ = 0;
    startTime_ = 0;
    totalIdleTime_ = 0;
    msBetweenFrames_ = 0;
    running_ = false;
    return initResult;
}

const double AppTimer::GetTimeBetweenFramesInMs() const {
    return msBetweenFrames_;
}

const double AppTimer::GetTotalRunningTimeInS() const {
    if (running_ == false) {
        return (lastPausedTime_ - startTime_ - totalIdleTime_) * msPerCpuCount_;
    }
        
    return (currentTime_ - startTime_ - totalIdleTime_) * msPerCpuCount_;
}

Result AppTimer::Start() {
    Result startResult;
    if (running_ == true) {
        // Calling start while running is okay, we just do nothing.
        return startResult;
    }

    LARGE_INTEGER currentTime {};
    if (QueryPerformanceCounter(&currentTime) == FALSE) {
        startResult.AppendError("AppTimer::Start() : Could not start timer.");
        return startResult;
    }

    startTime_ = currentTime.QuadPart;
    if (lastPausedTime_ > 0) {
        totalIdleTime_ += (startTime_ - lastPausedTime_);
    }
    running_ = true;

    return startResult;
}

Result AppTimer::Update() {
    Result updateResult;
    if (running_ == false) {
        msBetweenFrames_ = 0;
        return updateResult;
    }

    LARGE_INTEGER currentTime{};
    if (QueryPerformanceCounter(&currentTime) == FALSE) {
        updateResult.AppendError("AppTimer::Start() : Could not update timer.");
        return updateResult;
    }

    currentTime_ = currentTime.QuadPart;
    msBetweenFrames_ = static_cast<double>(currentTime_ - lastFrameTime_) * msPerCpuCount_;
    lastFrameTime_ = currentTime_;
    if (msBetweenFrames_ < 0) {
        msBetweenFrames_ = 0;
    }

    return updateResult;
}

Result AppTimer::Pause() {
    Result pauseResult;
    if (running_ == false) {
        // Calling pause while paused is okay, we just do nothing.
        return pauseResult;
    }

    LARGE_INTEGER currentTime{};
    if (QueryPerformanceCounter(&currentTime) == FALSE) {
        pauseResult.AppendError("AppTimer::Start() : Could not pause timer.");
        return pauseResult;
    }

    lastPausedTime_ = currentTime.QuadPart;
    running_ = false;

    return pauseResult;
}
