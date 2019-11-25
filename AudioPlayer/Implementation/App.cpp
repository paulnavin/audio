#include "App.hpp"

#include "App.hpp"
#include "EasyLogging++.hpp"
#include "Result.hpp"
#include "StringUtil.hpp"
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
        createWindowResult.AppendError("App::Init() : Error creating main window.");
        return createWindowResult;
    }

    initResult = engine3d_.Init(*mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 3D controller.");
        return initResult;
    }

    initResult = engine2d_.Init(*mainWindow_, engine3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 3D controller.");
        return initResult;
    }

    initResult = textManager2d_.Init(*mainWindow_, engine2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 2D text manager.");
        return initResult;
    }

    initResult = fpsText_.Init(
        engine2d_.GetDeviceContext2d(),
        textManager2d_.GetFpsTextFormat(),
        textManager2d_.GetWriteFactory(),
        textManager2d_.GetFpsBrush());
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 2D FPS text.");
        return initResult;
    }

    acceleratorTable_ = LoadAccelerators(appInstance_, MAKEINTRESOURCE(IDC_AUDIOPLAYER));

    LOG(INFO) << "App::Init() : Successful!";

    return Result{};
}

Result App::Run() {
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

    while (finished == false) {
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

        if (finished == false) {
            timer_.Update();

            if (showFps_ == true) {
                Result updateResult = UpdateFps();
                if (updateResult.HasErrors()) {
                    return updateResult;
                }
            }

            accumulatedTime += timer_.GetTimeBetweenFramesInS();
            loopCount = 0;
            while (accumulatedTime >= MS_PER_FRAME && loopCount < MAX_SKIP_FRAMES) {
                Update(MS_PER_FRAME);
                accumulatedTime -= MS_PER_FRAME;
                ++loopCount;
            }

            // peek into the future and generate the output
            Result renderResult = Render(accumulatedTime / MS_PER_FRAME);
            if (renderResult.HasErrors()) {
                return renderResult;
            }
        }
    }

    return Result{};
}

void App::Update(const double& dt) {
    UNREFERENCED_PARAMETER(dt);
}

Result App::Render(const double& dt) {
    Result renderResult{};

    // (1) Clear the screen.
    engine3d_.ClearBuffers();

    // (2) Draw any 3D stuff.
    UNREFERENCED_PARAMETER(dt);

    // (3) Draw any 2D stuff on top of the 3D stuff.
    if (showFps_ == true) {
        renderResult = RenderFps();
        if (renderResult.HasErrors()) {
            return renderResult;
        }
    }

    // (4) Present the buffers to the screen.
    return engine3d_.Present();
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    LOG(INFO) << "App::ShutDown() : Shut down!";
    mainWindow_ = nullptr;
}

Result App::RenderFps() {
    return fpsText_.RenderFps();
}

Result App::SetFpsText(const int64_t& newFps) {
    std::wostringstream fpsString{};
    fpsString.precision(6);
    fpsString << "FPS: " << newFps << std::endl;

    Result setTextResult = fpsText_.SetText(fpsString.str());
    if (setTextResult.HasErrors()) {
        setTextResult.AppendError("App::SetFpsText() : Could not set text on Text2d.");
    }

    return setTextResult;
}

Result App::UpdateFps() {
    ++totalAppFrames_;
    double currentTime = timer_.GetTotalRunningTimeInS();

    // Update once per second.
    if ((currentTime - lastFpsCalculationTime_) >= 1) {
        fps_ = totalAppFrames_;

        totalAppFrames_ = 0;
        lastFpsCalculationTime_ += 1;
        return SetFpsText(fps_);
    }

    return Result{};
}
