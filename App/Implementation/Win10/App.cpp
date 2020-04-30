#include <App/App.hpp>

#include <App/AppUserInput.hpp>
#include <App/Scene.hpp>
#include <Platform/Commander.hpp>
#include <Platform/ErrorHandling.hpp>
#include <Platform/ErrorDisplay.hpp>
#include <Platform/Logging.hpp>
#include <Platform/ResourceLocator.hpp>
#include <Platform/Window.hpp>
#include <Platform/WindowConfig.hpp>
#include <Platform/WindowManager.hpp>

Result App::Init(const AppInstance& appInstance, const ResourceLocator& resourceManager) {
    appInstance_ = appInstance;

    Result result = config_.LoadConfig(configFileName_);
    if (result.HasErrors()) {
        result.AppendError("App::Init() : Error loading app config from file.");
        result.AppendError(configFileName_.c_str());
        return result;
    }

    WindowManager& windowManager = WindowManager::GetInstance();
    ReturnIfResultError(
        windowManager.Init(appInstance_, mainWindowConfig_),
        "App::Init() : Error initialising WindowManager.");

    ReturnIfResultError(
        timer_.Init(),
        "App::Init() : Error initialising app timer.");

    ReturnIfResultError(
        windowManager.CreateNewWindow(mainWindowConfig_, &mainWindow_),
        "App::Init() : Error creating main window.");

    mainWindow_->SetWindowMessageHandler(this);

    ReturnIfResultError(
        graphicsEngine_.Init(mainWindow_, resourceManager),
        "App::Init() : Error initialising graphics engine.");

    ReturnIfResultError(
        inputManager_.Init(mainWindow_),
        "App::Init() : Error initialising input manager.");

    ReturnIfResultError(
        resourceManager_.Init(&graphicsEngine_, &keen_),
        "App::Init() : Error initialising resource manager.");

    keen_.SetAppCommandHandler(
        [this](const CommandId& command) {
        this->HandleAppCommand(command);
    });
    ReturnIfResultError(
        keen_.Init(),
        "App::Init() : Error initialising Billy Blaze.");

    ReturnIfResultError(
        audioEngine_.Init(),
        "App::Init() : Error initialising audio engine.");

    portal_.commander = &keen_;
    portal_.gfx = &graphicsEngine_;
    portal_.resourceManager = &resourceManager_;
    LOG(INFO) << "App::Init() : Successful!";
    initialised_ = true;

    return result;
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
            ReinitialiseScenes();
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
            graphicsEngine_.StartRender();
            for (Scene* scene : currentScenes_) {
                scene->Render(accumulatedTime / MS_PER_FRAME);
            }
            graphicsEngine_.EndRender();
        }
    }

    return Result{};
}

void App::ShutDown() {
    LOG(INFO) << "App::ShutDown() : Shut down!";

    PopAllScenes();

    audioEngine_.ShutDown();

    resourceManager_.ShutDown();

    // mainWindow_ will be destroyed by the WindowManager.
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

void App::OnCommandToggleFullScreen() {
    if (initialised_ == true) {
        paused_ = true;
        toggleFullScreen_ = true;
    }
}

void App::HandleAppCommand(const CommandId& command) {
    inputManager_.ActivateCommand(command);

}

Result App::SelectScene(Scene* newScene) {
    PopAllScenes();
    return PushScene(newScene);
}

Result App::PushScene(Scene* newScene) {
    if (currentScenes_.size() > 0) {
        currentScenes_.back()->SetTopScene(false);
    }
    Result initResult = newScene->Init(&portal_, &config_, &inputManager_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising scene when pushing.");
        return initResult;
    }

    newScene->SetTopScene(true);

    currentScenes_.push_back(newScene);

    return initResult;
}

void App::PopAllScenes() {
    while (currentScenes_.size() > 0) {
        PopScene();
    }
}

void App::PopScene() {
    if (currentScenes_.size() > 0) {
        currentScenes_.back()->ShutDown();
        currentScenes_.pop_back();
    }

    if (currentScenes_.size() > 0) {
        currentScenes_.back()->SetTopScene(true);
    }
}

void App::ReinitialiseScenes() {
    // Shut down in reverse order, from the top of the stack down.
    for (auto it = currentScenes_.rbegin(); it != currentScenes_.rend(); ++it) {
        (*it)->ShutDown();
    }

    // Then reinitialise in order again, from bottom of stack up.
    for (Scene* scene : currentScenes_) {
        scene->Init(&portal_, &config_, &inputManager_);
    }
}

Result App::SetWindowConfig(const WindowConfig& windowConfig) {
    mainWindowConfig_ = windowConfig;
    return Result{};
}

Result App::SetConfigFileName(const std::string& fileName) {
    // TODO: Check if it's actually a valid file.
    configFileName_ = fileName;
    return Result{};
}

void App::SetUserInputHandler(AppUserInput* appUserInputHandler) {
    userInputHandler_ = appUserInputHandler;
}

void App::Update(const double& dt) {
    inputManager_.Update();

    if (userInputHandler_ != nullptr) {
        userInputHandler_->Update();
    }
    for (Scene* scene : currentScenes_) {
        scene->Update(dt);
    }
}


Result App::UpdateFps() {
    ++totalAppFrames_;
    double currentTime = timer_.GetTotalRunningTimeInS();

    // Update once per second.
    if ((currentTime - lastFpsCalculationTime_) >= MS_PER_SECOND) {
        fps_ = totalAppFrames_;

        totalAppFrames_ = 0;
        lastFpsCalculationTime_ += MS_PER_SECOND;
        for (Scene* scene : currentScenes_) {
            scene->UpdateFps(fps_);
        }
    }

    return Result{};
}
