#pragma once

#include <Audio/XAudio.hpp>
#include <ErrorHandling/Result.hpp>

class AudioEngine {

public:
    AudioEngine() = default;
    ~AudioEngine() = default;

public:
    Result Init();
    void ShutDown();

private:
    Microsoft::WRL::ComPtr<IXAudio2> audioDevice_;
    IXAudio2MasteringVoice* hisMastersVoice_;
    Microsoft::WRL::ComPtr<IMFAttributes> sourceReaderConfig_;

    std::vector<BYTE> audioData;
};