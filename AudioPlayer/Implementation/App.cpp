#include "App.hpp"

#include "App.hpp"
#include "EasyLogging++.hpp"
#include "Result.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"

Result App::Init(const HINSTANCE& appInstance) {
    appInstance_ = appInstance;

    WindowManager& windowManager = WindowManager::GetInstance();
    Result initResult = windowManager.Init(appInstance_);

    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising WindowManager.");
        return initResult;
    }

    Result createTimerResult = timer_.Init();
    if (createTimerResult.HasErrors()) {
        createTimerResult.AppendError("App::Init() : Error initialising app timer.");
        return createTimerResult;
    }

    Result createWindowResult = windowManager.CreateNewWindow(&mainWindow_);
    if (createWindowResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error creating main window.");
        return initResult;
    }

    acceleratorTable_ = LoadAccelerators(appInstance_, MAKEINTRESOURCE(IDC_AUDIOPLAYER));

    LOG(INFO) << "App::Init() : Successful!";

    return Result{};
}

void App::Run() {
    LOG(INFO) << "App::Run() : Started!";
    mainWindow_->Show();

    // Loop taken from: https://gamedev.stackexchange.com/a/138780

    static constexpr DWORD FRAMES_PER_SECOND = 60;
    static constexpr DWORD MS_PER_SECOND = 1000;
    static constexpr DWORD MS_PER_FRAME = MS_PER_SECOND / FRAMES_PER_SECOND;
    static constexpr int32_t MAX_SKIP_FRAMES = 10;

    timer_.Start();

    double accumulatedTime = 0.0;       // stores the time accumulated by the rendered
    int32_t loopCount = 0;              // the number of completed loops while updating the game

    MSG msg = {};
    bool finished = false;

    while (!finished) {
        // Note: If you pass in the HWND to the main window instead of nullptr here, you
        //       won't get all messages, only those directly related to the window. So
        //       you'll miss things like if the user clicks the cross in the top corner.
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message) {
                finished = true;
                PostQuitMessage(0);
                break;
            } else {
                if (!TranslateAccelerator(msg.hwnd, acceleratorTable_, &msg)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        };

        timer_.Update();

        if (showFps_ == true) {
            UpdateFps();
        }

        accumulatedTime += timer_.GetTimeBetweenFramesInS();
        loopCount = 0;
        while (accumulatedTime >= MS_PER_FRAME && loopCount < MAX_SKIP_FRAMES) {
            Update(MS_PER_FRAME);
            accumulatedTime -= MS_PER_FRAME;
            ++loopCount;
        }

        // peek into the future and generate the output
        Render(accumulatedTime / MS_PER_FRAME);
    }
}

void App::Update(const double& dt) {
    UNREFERENCED_PARAMETER(dt);
}

void App::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    LOG(INFO) << "App::ShutDown() : Shut down!";
    mainWindow_ = nullptr;
}

void App::UpdateFps() {
    ++totalAppFrames_;
    double currentTime = timer_.GetTotalRunningTimeInS();

    // Update once per second.
    if ((currentTime - lastFpsCalculationTime_) >= 1) {
        fps_ = totalAppFrames_;

        totalAppFrames_ = 0;
        lastFpsCalculationTime_ += 1;
    }
}
