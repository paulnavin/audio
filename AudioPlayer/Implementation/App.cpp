#include "App.hpp"

#include <UserInterface/ErrorDisplay.hpp>
#include <UserInterface/Window.hpp>
#include <UserInterface/WindowConfig.hpp>
#include <UserInterface/WindowManager.hpp>
#include <Logging/EasyLogging++.hpp>
#include <FileSystem/ResourceManager.hpp>
#include <ErrorHandling/Result.hpp>

#include "Scene1Dj.hpp"
#include "Scene2Basic.hpp"
#include "Resource.h"

Result App::Init(const HINSTANCE& appInstance, const ResourceManager& resourceManager) {
    appInstance_ = appInstance;
    Result initResult{};

    initResult = config_.LoadConfig("someRubbish.ini");
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error loading app config.");
        return initResult;
    }

    WindowManager& windowManager = WindowManager::GetInstance();

    WindowConfig newWindowConfig{};
    newWindowConfig.height = config_.GetInt32("height", 200);
    newWindowConfig.width = config_.GetInt32("width", 300);
    newWindowConfig.showCursor_ = false;
    LoadStringW(appInstance_, IDS_APP_TITLE, newWindowConfig.title.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    LoadStringW(appInstance_, IDC_AUDIOPLAYER, newWindowConfig.mainWindowClassName_.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    newWindowConfig.appIcon_.Init(appInstance_, MAKEINTRESOURCE(IDI_AUDIOPLAYER));
    newWindowConfig.smallAppIcon_.Init(appInstance_, MAKEINTRESOURCE(IDI_MONKEY_ICON));
    newWindowConfig.mouseCursor_.Init(appInstance_, MAKEINTRESOURCE(IDC_DARK_OXYGEN_CURSOR_NORMAL));

    initResult = windowManager.Init(appInstance_, newWindowConfig);

    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising WindowManager.");
        return initResult;
    }

    initResult = timer_.Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising app timer.");
        return initResult;
    }

    initResult = windowManager.CreateNewWindow(newWindowConfig, &mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error creating main window.");
        return initResult;
    }
    mainWindow_->SetWindowMessageHandler(this);

    initResult = graphicsEngine_.Init(*mainWindow_, resourceManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising graphics engine.");
        return initResult;
    }

    initResult = inputManager_.Init(mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising input manager.");
        return initResult;
    }

    acceleratorTable_ = LoadAccelerators(appInstance_, MAKEINTRESOURCE(IDC_AUDIOPLAYER));

    initResult = userInputHandler_.Init(this, &inputManager_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising user input.");
        return initResult;
    }

    scenes_[0] = new Scene1Dj();
    scenes_[1] = new Scene2Basic();

    initResult = SelectScene(0);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising scene1.");
        return initResult;
    }

    LOG(INFO) << "App::Init() : Successful!";

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
                PostQuitMessage(0);
                break;
            } else {
                if (!TranslateAccelerator(msg.hwnd, acceleratorTable_, &msg)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        };
        
        if (resizeRequired_ == true || toggleFullScreen_ == true) {
            if (toggleFullScreen_ == true) {
                graphicsEngine_.ToggleFullScreen();
                toggleFullScreen_ = false;
            }
            graphicsEngine_.Resize();
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
            graphicsEngine_.Render(accumulatedTime / MS_PER_FRAME);
        }
    }

    return Result{};
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    LOG(INFO) << "App::ShutDown() : Shut down!";

    for (uint8_t i = 0; i < SCENE_COUNT; ++i) {
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

    paused_ = true;
    resizeRequired_ = true;
}

void App::OnMaximise() {
    LOG(INFO) << "App::OnMaximise() : Boogie woogie!";

    paused_ = true;
    resizeRequired_ = true;
}

void App::OnRestore() {
    LOG(INFO) << "App::OnRestore() : Boogie woogie!";

    paused_ = true;
    resizeRequired_ = true;
}

void App::OnStartSizeOrMove() {
    LOG(INFO) << "App::OnStartSizeOrMove() : Boogie woogie!";
    paused_ = true;
}

void App::OnFinishSizeOrMove() {
    LOG(INFO) << "App::OnFinishSizeOrMove() : Boogie woogie!";
    resizeRequired_ = true;
}

void App::OnCommandNextDisplayConfig() {
    paused_ = true;
    resizeRequired_ = true;
    graphicsEngine_.NextDisplayConfig();
}

void App::OnCommandPreviousDisplayConfig() {
    paused_ = true;
    resizeRequired_ = true;
    graphicsEngine_.PreviousDisplayConfig();
}

void App::OnCommandQuit() {
    OnClose();
}

void App::OnCommandResetDisplayConfig() {
    paused_ = true;
    resizeRequired_ = true;
    graphicsEngine_.ResetDisplayConfig();
}

void App::OnCommandToggleScene() {
    paused_ = true;
    resizeRequired_ = true;

    scenes_[currentSceneId_]->ShutDown();

    currentSceneId_ = static_cast<uint8_t>((currentSceneId_ + 1) % SCENE_COUNT);

    SelectScene(currentSceneId_);
}

void App::OnCommandToggleFullScreen() {
    paused_ = true;
    toggleFullScreen_ = true;
}

void App::UpdateMousePosition(const float& x, const float& y) {
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
