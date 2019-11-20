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

    LOG(INFO) << "Successfully initialised WindowManager!";

    Result createWindowResult = windowManager.CreateNewWindow(&mainWindow_);
    if (createWindowResult.HasErrors()) {
        initResult.AppendError("App::Init() : Error creating main window.");
        return initResult;
    }

    acceleratorTable_ = LoadAccelerators(appInstance_, MAKEINTRESOURCE(IDC_AUDIOPLAYER));
    
    return Result{};
}

void App::Run() {
    mainWindow_->Show();

    // Loop taken from: https://gamedev.stackexchange.com/a/138780

    static constexpr DWORD FRAMES_PER_SECOND = 60;
    static constexpr DWORD MS_PER_FRAME = 1000 / 60;

    MSG msg = {};
    bool finished = false;

    while (!finished) {
        DWORD currentTick = GetTickCount();
        DWORD endTick = currentTick + MS_PER_FRAME;

        while (currentTick < endTick) {
            // Note: If you pass in the HWND to the main window instead of nullptr here, you
            //       won't get all messages, only those directly related to the window. So
            //       you'll miss things like if the user clicks the cross in the top corner.
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
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
                currentTick = GetTickCount();
            } else {
                break;
            }
        }
        //processFrame();
    }
}

void App::ShutDown() {
    // mainWindow_ will be destroyed by the WindowManager.
    mainWindow_ = nullptr;
}
