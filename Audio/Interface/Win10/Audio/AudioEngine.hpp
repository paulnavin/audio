#pragma once

#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

class AudioEngine {

public:
    AudioEngine() = default;
    ~AudioEngine() = default;

public:
    Result Init();
};