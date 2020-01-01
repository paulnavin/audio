#include "App.hpp"

#include <UserInterface/WindowConfig.hpp>
#include <UserInterface/Window.hpp>
#include <UserInput/CoreCommands.hpp>
#include <Utility/EasyLogging++.hpp>
#include <Utility/Result.hpp>

#include "ModelBasic2d.hpp"
#include "ModelDj.hpp"
#include "ModelStarField.hpp"
#include "ModelTriangle.hpp"
#include "Resource.h"
#include "WindowManager.hpp"

Result App::Init(const HINSTANCE& appInstance) {
    appInstance_ = appInstance;

    WindowManager& windowManager = WindowManager::GetInstance();
    Result initResult = windowManager.Init(appInstance_);

    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising WindowManager.");
        return initResult;
    }

    initResult = timer_.Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error initialising app timer.");
        return initResult;
    }

    initResult = config_.LoadConfig("someRubbish.ini");
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error loading app config.");
        return initResult;
    }

    static constexpr size_t MAX_LOADSTRING = 100;
    WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
    LoadStringW(appInstance_, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

    WindowConfig newWindowConfig{};
    newWindowConfig.height = config_.GetInt32("height", 200);
    newWindowConfig.width = config_.GetInt32("width", 300);
    newWindowConfig.title = std::wstring(szTitle);

    initResult = windowManager.CreateNewWindow(newWindowConfig, &mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error creating main window.");
        return initResult;
    }

    initResult = engine3d_.Init(*mainWindow_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 3D controller.");
        return initResult;
    }

    model3d_ = new ModelStarField();
    //model3d_ = new ModelTriangle();
    initResult = model3d_->Init();
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 3D model.");
        return initResult;
    }

    initResult = engine3d_.InitGraphics(*model3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 3D graphics.");
        return initResult;
    }

    initResult = engine2d_.Init(*mainWindow_, engine3d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising 2D controller.");
        return initResult;
    }

    djModel2d_ = new ModelDj();
    initResult = djModel2d_->Init(engine2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising DJ 2D model.");
        return initResult;
    }
    djModel2d_->SetShowFps(showFps_);

    basicModel2d_ = new ModelBasic2d();
    initResult = basicModel2d_->Init(engine2d_);
    if (initResult.HasErrors()) {
        initResult.AppendError("Window::Init() : Error initialising basic 2D model.");
        return initResult;
    }
    basicModel2d_->SetShowFps(showFps_);

    SetActive2dModel(djModel2d_);

    acceleratorTable_ = LoadAccelerators(appInstance_, MAKEINTRESOURCE(IDC_AUDIOPLAYER));

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
            Result renderResult = Render(accumulatedTime / MS_PER_FRAME);
            if (renderResult.HasErrors()) {
                return renderResult;
            }
        }
    }

    return Result{};
}

void App::Update(const double& dt) {
    inputManager_.Update();

    const InputManager::CommandMap* activeCommands = inputManager_.GetActiveKeyMap();
    for (auto command : *activeCommands) {
        if (command.first == ToggleFps) {
            showFps_ = !showFps_;
            active2dModel_->SetShowFps(showFps_);
        } else if (command.first == ToggleMousePosition) {
            showMousePosition_ = !showMousePosition_;
            active2dModel_->SetShowMousePosition(showMousePosition_);
        } else if (command.first == Toggle2dModel) {
            if (active2dModel_ == djModel2d_) {
                SetActive2dModel(basicModel2d_);
            } else {
                SetActive2dModel(djModel2d_);
            }
        }
    }

    active2dModel_->SetMousePosition(inputManager_.GetMouseXPos(), inputManager_.GetMouseYPos());
    active2dModel_->Update(dt);
}

Result App::Render(const double& dt) {
    Result renderResult{};

    // (1) Clear the screen.
    engine3d_.ClearBuffers();

    // (2) Draw any 3D stuff.
    engine3d_.RenderVertices();

    // (3) Draw any 2D stuff on top of the 3D stuff.
    engine2d_.RenderModel(dt);

    // (4) Present the buffers to the screen.
    return engine3d_.Present();
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    LOG(INFO) << "App::ShutDown() : Shut down!";

    mainWindow_ = nullptr;

    if (model3d_ != nullptr) {
        delete model3d_;
    }
    model3d_ = nullptr;

    if (djModel2d_ != nullptr) {
        delete djModel2d_;
    }
    djModel2d_ = nullptr;

    if (basicModel2d_ != nullptr) {
        delete basicModel2d_;
    }
    basicModel2d_ = nullptr;
}

void App::SetActive2dModel(Model2d* newActiveModel) {
    active2dModel_ = newActiveModel;
    engine2d_.SetModel(active2dModel_);
}

Result App::UpdateFps() {
    ++totalAppFrames_;
    double currentTime = timer_.GetTotalRunningTimeInS();

    // Update once per second.
    if ((currentTime - lastFpsCalculationTime_) >= MS_PER_SECOND) {
        fps_ = totalAppFrames_;

        totalAppFrames_ = 0;
        lastFpsCalculationTime_ += MS_PER_SECOND;
        active2dModel_->SetFps(fps_);
    }

    return Result{};
}
