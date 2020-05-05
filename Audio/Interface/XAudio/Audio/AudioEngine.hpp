#pragma once

#include <Audio/XAudio.hpp>
#include <Platform/ErrorHandling.hpp>
#include <Platform/Stl.hpp>

struct MySource;

class AudioEngine {

public:
    AudioEngine() = default;
    ~AudioEngine() = default;

public:
    Result Init();
    void ShutDown();

    HRESULT PlayAudioStream(MySource *pMySource);

private:
    Microsoft::WRL::ComPtr<IXAudio2> audioDevice_;
    IXAudio2MasteringVoice* hisMastersVoice_;
    Microsoft::WRL::ComPtr<IMFAttributes> sourceReaderConfig_;

    BYTE* audioData;
};