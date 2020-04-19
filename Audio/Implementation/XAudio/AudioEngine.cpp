#include <Audio/AudioEngine.hpp>

Result AudioEngine::Init() {
    Result result{};

    // Get the main XAudio2 device.
    ReturnIfHrError(
        XAudio2Create(audioDevice_.GetAddressOf()),
        "AudioEngine::Init() : Unable to create XAudio device.");

    // Create his master's voice.
    ReturnIfHrError(
        audioDevice_->CreateMasteringVoice(&hisMastersVoice_),
        "AudioEngine::Init() : Unable to create master voice.");

    ReturnIfHrError(
        MFStartup(MF_VERSION),
        "AudioEngine::Init() : Unable to initialise Media Foundations.");

    ReturnIfHrError(
        MFCreateAttributes(sourceReaderConfig_.GetAddressOf(), 1),
        "AudioEngine::Init() : Unable to create Media Foundations source reader config.");

    ReturnIfHrError(
        sourceReaderConfig_->SetUINT32(MF_LOW_LATENCY, true),
        "AudioEngine::Init() : Unable to set Media Foundations config to low latency.");

    DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
    Microsoft::WRL::ComPtr<IMFSourceReader> sourceReader;
    const char* fileNameRaw = "C:\\Test.mp3";
    std::wstring fileName = L"C:\\Test.mp3";
    Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
    GUID majorType{};
    GUID subType{};
    ReturnIfHrError(
        MFCreateSourceReaderFromURL(fileName.c_str(), sourceReaderConfig_.Get(), sourceReader.GetAddressOf()),
        "AudioEngine::Init() : Unable to load audio file.");
    if (sourceReader == nullptr) {
        result.AppendError("AudioEngine::Init() : Audio file not found.");
        result.AppendError(fileNameRaw);
        return result;
    }

    ReturnIfHrError(
        sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false),
        "AudioEngine::Init() : Unable to turn off source reader all stream selection.");

    ReturnIfHrError(
        sourceReader->SetStreamSelection(streamIndex, true),
        "AudioEngine::Init() : Unable to initialise single stream.");

    ReturnIfHrError(
        sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf()),
        "AudioEngine::Init() : Unable to get native media type.");

    ReturnIfHrError(
        nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType),
        "AudioEngine::Init() : Unable to get major media type.");
    if (majorType != MFMediaType_Audio) {
        result.AppendError("AudioEngine::Init() : Wrong major media type (not audio).");
        return result;
    }

    ReturnIfHrError(
        nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType),
        "AudioEngine::Init() : Unable to get minor media type.");
    if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM) {
        // the audio file is uncompressed
    } else {
        // the audio file is compressed; we have to decompress it first
        Microsoft::WRL::ComPtr<IMFMediaType> partialType = nullptr;
        ReturnIfHrError(
            MFCreateMediaType(partialType.GetAddressOf()),
            "AudioEngine::Init() : Unable to create partial media type.");

        ReturnIfHrError(
            partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio),
            "AudioEngine::Init() : Unable to set major type of partial media type to audio.");

        ReturnIfHrError(
            partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM),
            "AudioEngine::Init() : Unable to set sub type of partial media type to uncompressed.");

        ReturnIfHrError(
            sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType.Get()),
            "AudioEngine::Init() : Unable to set source reader current media type to partial type.");
    }
        Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
        WAVEFORMATEX* waveFormatEx;
        uint32_t waveFormatLength;
        ReturnIfHrError(
            sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf()),
            "AudioEngine::Init() : Unable to get the current media type from the source stream.");
        ReturnIfHrError(
            MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), &waveFormatEx, &waveFormatLength),
            "AudioEngine::Init() : Unable to get the current media type from the source stream.");

        ReturnIfHrError(
            sourceReader->SetStreamSelection(streamIndex, true),
            "AudioEngine::Init() : Unable to set single stream again.");

        // copy data into byte vector
        Microsoft::WRL::ComPtr<IMFSample> sample = nullptr;
        Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer = nullptr;
        BYTE* localAudioData = NULL;
        DWORD localAudioDataLength = 0;

        while (true) {
            DWORD flags = 0;
            ReturnIfHrError(
                sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf()),
                "AudioEngine::Init() : Unable to read samples.");

            // check whether the data is still valid
            if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
                break;

            // check for eof
            if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
                break;

            if (sample == nullptr)
                continue;

            // convert data to contiguous buffer
            ReturnIfHrError(
                sample->ConvertToContiguousBuffer(buffer.GetAddressOf()),
                "AudioEngine::Init() : Unable to convert samples to a contiguous buffer.");

            // lock buffer and copy data to local memory
            ReturnIfHrError(
                buffer->Lock(&localAudioData, nullptr, &localAudioDataLength),
                "AudioEngine::Init() : Unable to lock audio buffer.");

            for (size_t i = 0; i < localAudioDataLength; i++)
                audioData.push_back(localAudioData[i]);

            // unlock the buffer
            ReturnIfHrError(
                buffer->Unlock(),
                "AudioEngine::Init() : Unable to unlock audio buffer.");
            localAudioData = nullptr;
        }

    return result;
}

void AudioEngine::ShutDown() {
    // shut down the media foundation
    MFShutdown();

    // destroy the master voice
    if (hisMastersVoice_) {
        hisMastersVoice_->DestroyVoice();
    }

    // stop the engine
    if (audioDevice_) {
        audioDevice_->StopEngine();
    }
}
