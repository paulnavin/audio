#include <App/App.hpp>

#include <App/Scene.hpp>
#include <Display/ErrorDisplay.hpp>
#include <Display/Window.hpp>
#include <Display/WindowConfig.hpp>
#include <Display/WindowManager.hpp>
#include <Logging/EasyLogging++.hpp>
#include <FileSystem/ResourceManager.hpp>
#include <ErrorHandling/Result.hpp>

Result App::Init(const HINSTANCE& appInstance, const ResourceManager& resourceManager) {
    appInstance_ = appInstance;
    Result initResult{};

    WindowManager& windowManager = WindowManager::GetInstance();
    initResult = windowManager.Init(appInstance_, mainWindowConfig_);

    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising WindowManager.");
        return initResult;
    }

    initResult = timer_.Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising app timer.");
        return initResult;
    }

    initResult = windowManager.CreateNewWindow(mainWindowConfig_, &mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error creating main window.");
        return initResult;
    }
    mainWindow_->SetWindowMessageHandler(this);

    initResult = graphicsEngine_.Init(mainWindow_, resourceManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising graphics engine.");
        return initResult;
    }

    initResult = inputManager_.Init(mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising input manager.");
        return initResult;
    }

    initResult = userInputHandler_.Init(this, &inputManager_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising user input.");
        return initResult;
    }

    LOG(INFO) << "App::Init() : Successful!";
    currentSceneId_ = 0;
    initialised_ = true;

    return Result{};
}

Result App::Run() {
    LOG(INFO) << "App::Run() : Started!";
    mainWindow_->Show();

    // Loop taken from: https://gamedev.stackexchange.com/a/138780

    timer_.Start();
    timer_.Update();

    double accumulatedTime = 0.0;       // stores the time accumulated by the rendered
    int32_t loopCount = 0;              // the number of completed loops while updating the game

    MSG msg = {};

    while (finished_ == false) {
        // Note: If you pass in the HWND to the main window instead of nullptr here, you
        //       won't get all messages, only those directly related to the window. So
        //       you'll miss things like if the user clicks the cross in the top corner.
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message) {
                finished_ = true;
                break;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        };

        if (resizeRequired_ == true || toggleFullScreen_ == true) {
            if (toggleFullScreen_ == true) {
                graphicsEngine_.ToggleFullScreen();
                toggleFullScreen_ = false;
            }
            graphicsEngine_.Resize();
            SelectScene(currentSceneId_);
            resizeRequired_ = false;
            paused_ = false;
        }

        if ((finished_ == false) && (paused_ == false)) {
            timer_.Update();

            if (showFps_ == true) {
                Result updateResult = UpdateFps();
                if (updateResult.HasErrors()) {
                    return updateResult;
                }
            }

            accumulatedTime += timer_.GetTimeBetweenFramesInMs();

            // TODO: Is this actually right???
            loopCount = 0;
            while (accumulatedTime >= MS_PER_FRAME && loopCount < MAX_SKIP_FRAMES) {
                Update(MS_PER_FRAME);
                accumulatedTime -= MS_PER_FRAME;
                ++loopCount;
            }

            // TODO: Is this actually right???
            // peek into the future and generate the output
            scenes_[currentSceneId_]->Render(accumulatedTime / MS_PER_FRAME);
        }
    }

    return Result{};
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    LOG(INFO) << "App::ShutDown() : Shut down!";

    for (uint8_t i = 0; i < ACTUAL_SCENE_COUNT; ++i) {
        if (i == currentSceneId_) {
            scenes_[i]->ShutDown();
        }
        delete scenes_[i];
        scenes_[i] = nullptr;
    }

    mainWindow_ = nullptr;
}

void App::OnActivate() {
    LOG(INFO) << "App::OnActivate() : Boogie woogie!";
}

void App::OnClose() {
    LOG(INFO) << "App::OnClose() : Boogie woogie!";
    finished_ = true;
    PostQuitMessage(0);
}

void App::OnMinimise() {
    LOG(INFO) << "App::OnMinimise() : Boogie woogie!";

    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
    }
}

void App::OnMaximise() {
    LOG(INFO) << "App::OnMaximise() : Boogie woogie!";

    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
    }
}

void App::OnRestore() {
    LOG(INFO) << "App::OnRestore() : Boogie woogie!";

    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
    }
}

void App::OnStartSizeOrMove() {
    LOG(INFO) << "App::OnStartSizeOrMove() : Boogie woogie!";
    paused_ = true;
}

void App::OnFinishSizeOrMove() {
    LOG(INFO) << "App::OnFinishSizeOrMove() : Boogie woogie!";

    if (initialised_ == true) {
        resizeRequired_ = true;
    }
}

void App::OnCommandNextDisplayConfig() {
    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
        graphicsEngine_.NextDisplayConfig();
    }
}

void App::OnCommandPreviousDisplayConfig() {
    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
        graphicsEngine_.PreviousDisplayConfig();
    }
}

void App::OnCommandQuit() {
    OnClose();
}

void App::OnCommandResetDisplayConfig() {
    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;
        graphicsEngine_.ResetDisplayConfig();
    }
}

void App::OnCommandToggleScene() {
    if (initialised_ == true) {
        paused_ = true;
        resizeRequired_ = true;

        scenes_[currentSceneId_]->ShutDown();

        currentSceneId_ = static_cast<uint8_t>((currentSceneId_ + 1) % ACTUAL_SCENE_COUNT);

        SelectScene(currentSceneId_);
    }
}

void App::OnCommandToggleFullScreen() {
    if (initialised_ == true) {
        paused_ = true;
        toggleFullScreen_ = true;
    }
}

void App::UpdateMousePosition(const float& x, const float& y) {
    // TODO: Make a member pointer for current scene, instead of dereferencing the array.
    scenes_[currentSceneId_]->UpdateMousePosition(x, y);
}

Result App::SelectScene(const uint8_t& newSceneId) {
    if (currentSceneId_ != UINT8_MAX) {
        scenes_[currentSceneId_]->ShutDown();
    }

    Result initResult = scenes_[newSceneId]->Init(&graphicsEngine_, &config_, &inputManager_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising scene1.");
        return initResult;
    }

    currentSceneId_ = newSceneId;

    return initResult;
}

Result App::InitWindowConfig(const WindowConfig& windowConfig) {
    mainWindowConfig_ = windowConfig;
    return Result{};
}

Result App::InitConfig(const std::string& fileName) {
    Result initResult = config_.LoadConfig(fileName);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::InitConfig() : Error loading app config.");
    }
    return initResult;
}

void App::Update(const double& dt) {
    inputManager_.Update();

    userInputHandler_.Update();
    scenes_[currentSceneId_]->Update(dt);
}


Result App::UpdateFps() {
    ++totalAppFrames_;
    double currentTime = timer_.GetTotalRunningTimeInS();

    // Update once per second.
    if ((currentTime - lastFpsCalculationTime_) >= MS_PER_SECOND) {
        fps_ = totalAppFrames_;

        totalAppFrames_ = 0;
        lastFpsCalculationTime_ += MS_PER_SECOND;
        scenes_[currentSceneId_]->UpdateFps(fps_);
    }

    return Result{};
}
