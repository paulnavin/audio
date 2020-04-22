#include <Audio/AudioEngine.hpp>

#include <Platform/Stl.hpp>


#define PI 3.1415926535897932384626433832795
#define PI2 2 * PI

#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

typedef struct MySource {
    float sineFrequency_ = 440.0;
    double pos_ = 0.0;
    double cycleLength_ = 44100.0 / sineFrequency_;
    uint32_t cycleCount_ = 0;

    WAVEFORMATEX* pwfx_ = NULL;

    HRESULT setFormat(WAVEFORMATEX* pwfx) {
        pwfx_ = pwfx;
        cycleLength_ = pwfx_->nSamplesPerSec / sineFrequency_;
        return 0;
    }

    HRESULT loadData(UINT32 numFramesAvailable, BYTE* pData, DWORD* flags) {
        float* out = (float*)pData;

        for (uint32_t frame = 0; frame < numFramesAvailable; ++frame) {
            float val = (float)(sin(2 * PI * (pos_ / cycleLength_)));

            for (int chan = 0; chan < pwfx_->nChannels; ++chan) {
                out[(frame * pwfx_->nChannels) + chan] = val;
            }

            pos_ += 1.0;
            if (pos_ > cycleLength_) {
                pos_ -= cycleLength_;
            }
        }

        ++cycleCount_;
        if (cycleCount_ > 5) {
            *flags = AUDCLNT_BUFFERFLAGS_SILENT;
        }

        return 0;
    }

} MySource;

Result AudioEngine::Init() {
    Result result{};

    //// Get the main XAudio2 device.
    //ReturnIfHrError(
    //    XAudio2Create(audioDevice_.GetAddressOf()),
    //    "AudioEngine::Init() : Unable to create XAudio device.");

    //// Create his master's voice.
    //ReturnIfHrError(
    //    audioDevice_->CreateMasteringVoice(&hisMastersVoice_),
    //    "AudioEngine::Init() : Unable to create master voice.");

    //ReturnIfHrError(
    //    MFStartup(MF_VERSION),
    //    "AudioEngine::Init() : Unable to initialise Media Foundations.");

    //ReturnIfHrError(
    //    MFCreateAttributes(sourceReaderConfig_.GetAddressOf(), 1),
    //    "AudioEngine::Init() : Unable to create Media Foundations source reader config.");

    //ReturnIfHrError(
    //    sourceReaderConfig_->SetUINT32(MF_LOW_LATENCY, true),
    //    "AudioEngine::Init() : Unable to set Media Foundations config to low latency.");

    //DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
    //Microsoft::WRL::ComPtr<IMFSourceReader> sourceReader;
    //const char* fileNameRaw = "C:\\Test.mp3";
    //std::wstring fileName = L"C:\\Test.mp3";
    //Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
    //GUID majorType{};
    //GUID subType{};
    //ReturnIfHrError(
    //    MFCreateSourceReaderFromURL(fileName.c_str(), sourceReaderConfig_.Get(), sourceReader.GetAddressOf()),
    //    "AudioEngine::Init() : Unable to load audio file.");
    //if (sourceReader == nullptr) {
    //    result.AppendError("AudioEngine::Init() : Audio file not found.");
    //    result.AppendError(fileNameRaw);
    //    return result;
    //}

    //ReturnIfHrError(
    //    sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false),
    //    "AudioEngine::Init() : Unable to turn off source reader all stream selection.");

    //ReturnIfHrError(
    //    sourceReader->SetStreamSelection(streamIndex, true),
    //    "AudioEngine::Init() : Unable to initialise single stream.");

    //ReturnIfHrError(
    //    sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf()),
    //    "AudioEngine::Init() : Unable to get native media type.");

    //ReturnIfHrError(
    //    nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType),
    //    "AudioEngine::Init() : Unable to get major media type.");
    //if (majorType != MFMediaType_Audio) {
    //    result.AppendError("AudioEngine::Init() : Wrong major media type (not audio).");
    //    return result;
    //}

    //ReturnIfHrError(
    //    nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType),
    //    "AudioEngine::Init() : Unable to get minor media type.");
    //if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM) {
    //    // the audio file is uncompressed
    //} else {
    //    // the audio file is compressed; we have to decompress it first
    //    Microsoft::WRL::ComPtr<IMFMediaType> partialType = nullptr;
    //    ReturnIfHrError(
    //        MFCreateMediaType(partialType.GetAddressOf()),
    //        "AudioEngine::Init() : Unable to create partial media type.");

    //    ReturnIfHrError(
    //        partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio),
    //        "AudioEngine::Init() : Unable to set major type of partial media type to audio.");

    //    ReturnIfHrError(
    //        partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM),
    //        "AudioEngine::Init() : Unable to set sub type of partial media type to uncompressed.");

    //    ReturnIfHrError(
    //        sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType.Get()),
    //        "AudioEngine::Init() : Unable to set source reader current media type to partial type.");
    //}
    //    Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
    //    WAVEFORMATEX* waveFormatEx;
    //    uint32_t waveFormatLength;
    //    ReturnIfHrError(
    //        sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf()),
    //        "AudioEngine::Init() : Unable to get the current media type from the source stream.");
    //    ReturnIfHrError(
    //        MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), &waveFormatEx, &waveFormatLength),
    //        "AudioEngine::Init() : Unable to get the current media type from the source stream.");

    //    ReturnIfHrError(
    //        sourceReader->SetStreamSelection(streamIndex, true),
    //        "AudioEngine::Init() : Unable to set single stream again.");

    //    // copy data into byte vector
    //    Microsoft::WRL::ComPtr<IMFSample> sample = nullptr;
    //    Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer = nullptr;
    //    BYTE* localAudioData = NULL;
    //    DWORD localAudioDataLength = 0;

    //    while (true) {
    //        DWORD flags = 0;
    //        ReturnIfHrError(
    //            sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf()),
    //            "AudioEngine::Init() : Unable to read samples.");

    //        // check whether the data is still valid
    //        if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
    //            break;

    //        // check for eof
    //        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
    //            break;

    //        if (sample == nullptr)
    //            continue;

    //        // convert data to contiguous buffer
    //        ReturnIfHrError(
    //            sample->ConvertToContiguousBuffer(buffer.GetAddressOf()),
    //            "AudioEngine::Init() : Unable to convert samples to a contiguous buffer.");

    //        // lock buffer and copy data to local memory
    //        ReturnIfHrError(
    //            buffer->Lock(&localAudioData, nullptr, &localAudioDataLength),
    //            "AudioEngine::Init() : Unable to lock audio buffer.");

    //        for (size_t i = 0; i < localAudioDataLength; i++)
    //            audioData.push_back(localAudioData[i]);

    //        // unlock the buffer
    //        ReturnIfHrError(
    //            buffer->Unlock(),
    //            "AudioEngine::Init() : Unable to unlock audio buffer.");
    //        localAudioData = nullptr;
    //    }

        MySource source;
        ReturnIfHrError(
            PlayAudioStream(&source),
            "AudioEngine::Init() : Unable to play random stream.");

    return result;
}

// From https://docs.microsoft.com/en-gb/windows/win32/coreaudio/rendering-a-stream?redirectedfrom=MSDN

//-----------------------------------------------------------
// Play an audio stream on the default audio rendering
// device. The PlayAudioStream function allocates a shared
// buffer big enough to hold one second of PCM audio data.
// The function uses this buffer to stream data to the
// rendering device. The inner loop runs every 1/2 second.
//-----------------------------------------------------------

// REFERENCE_TIME time units per second and per millisecond
#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

HRESULT AudioEngine::PlayAudioStream(MySource* pMySource) {
    HRESULT hr;
    REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
    REFERENCE_TIME hnsActualDuration;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IAudioClient *pAudioClient = NULL;
    IAudioRenderClient *pRenderClient = NULL;
    WAVEFORMATEX *pwfx = NULL;
    UINT32 bufferFrameCount;
    UINT32 numFramesAvailable;
    UINT32 numFramesPadding;
    BYTE *pData;
    DWORD flags = 0;

    hr = CoCreateInstance(
        CLSID_MMDeviceEnumerator, NULL,
        CLSCTX_ALL, IID_IMMDeviceEnumerator,
        (void**)&pEnumerator);
    EXIT_ON_ERROR(hr)

        hr = pEnumerator->GetDefaultAudioEndpoint(
            eRender, eConsole, &pDevice);
    EXIT_ON_ERROR(hr)

        hr = pDevice->Activate(
            IID_IAudioClient, CLSCTX_ALL,
            NULL, (void**)&pAudioClient);
    EXIT_ON_ERROR(hr)

        hr = pAudioClient->GetMixFormat(&pwfx);
    EXIT_ON_ERROR(hr)

        hr = pAudioClient->Initialize(
            AUDCLNT_SHAREMODE_SHARED,
            0,
            hnsRequestedDuration,
            0,
            pwfx,
            NULL);
    EXIT_ON_ERROR(hr)

    // Tell the audio source which format to use.
        hr = pMySource->setFormat(pwfx);
    EXIT_ON_ERROR(hr)

    // Get the actual size of the allocated buffer.
        hr = pAudioClient->GetBufferSize(&bufferFrameCount);
    EXIT_ON_ERROR(hr)

        hr = pAudioClient->GetService(
            IID_IAudioRenderClient,
            (void**)&pRenderClient);
    EXIT_ON_ERROR(hr)

    // Grab the entire buffer for the initial fill operation.
        hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
    EXIT_ON_ERROR(hr)

    // Load the initial data into the shared buffer.
        hr = pMySource->loadData(bufferFrameCount, pData, &flags);
    EXIT_ON_ERROR(hr)

        hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
    EXIT_ON_ERROR(hr)

    // Calculate the actual duration of the allocated buffer.
        hnsActualDuration = static_cast<REFERENCE_TIME>((double)REFTIMES_PER_SEC *
        bufferFrameCount / pwfx->nSamplesPerSec);

    hr = pAudioClient->Start();  // Start playing.
    EXIT_ON_ERROR(hr)

    // Each loop fills about half of the shared buffer.
    while (flags != AUDCLNT_BUFFERFLAGS_SILENT) {
        // Sleep for half the buffer duration.
        Sleep((DWORD)(hnsActualDuration / REFTIMES_PER_MILLISEC / 2));

        // See how much buffer space is available.
        hr = pAudioClient->GetCurrentPadding(&numFramesPadding);
        EXIT_ON_ERROR(hr)

            numFramesAvailable = bufferFrameCount - numFramesPadding;

            // Grab all the available space in the shared buffer.
        hr = pRenderClient->GetBuffer(numFramesAvailable, &pData);
        EXIT_ON_ERROR(hr)

        // Get next 1/2-second of data from the audio source.
            hr = pMySource->loadData(numFramesAvailable, pData, &flags);
        EXIT_ON_ERROR(hr)

            hr = pRenderClient->ReleaseBuffer(numFramesAvailable, flags);
        EXIT_ON_ERROR(hr)
    }

        // Wait for last data in buffer to play before stopping.
    Sleep((DWORD)(hnsActualDuration / REFTIMES_PER_MILLISEC / 2));

    hr = pAudioClient->Stop();  // Stop playing.
    EXIT_ON_ERROR(hr)

        Exit:
    CoTaskMemFree(pwfx);
    SAFE_RELEASE(pEnumerator)
        SAFE_RELEASE(pDevice)
        SAFE_RELEASE(pAudioClient)
        SAFE_RELEASE(pRenderClient)

        return 0;
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
