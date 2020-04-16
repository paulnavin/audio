#include "AudioPlayerApp.hpp"

#include <ErrorHandling/Result.hpp>
#include <FileSystem/ResourceLocator.hpp>
#include <Display/WindowConfig.hpp>
#include <Platform/AppInstance.hpp>

#include "AudioPlayerUserInputCommands.hpp"
#include "Win10/resource.h"

Result AudioPlayerApp::Init(const AppInstance& appInstance, const ResourceLocator& resourceManager) {
    Result initResult{};

    std::string configDirectoryName = resourceManager.GetUserConfigDirectoryName();
    configDirectoryName.append("\\config.txt");
    SetConfigFileName(configDirectoryName);

    WindowConfig newWindowConfig{};
    newWindowConfig.height = config_.GetInt32("height", 200);
    newWindowConfig.width = config_.GetInt32("width", 300);
    newWindowConfig.showCursor_ = false;
    LoadString(appInstance.appHandle, IDS_APP_TITLE, newWindowConfig.title.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    LoadString(appInstance.appHandle, IDC_AUDIOPLAYER, newWindowConfig.mainWindowClassName_.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    newWindowConfig.appIcon_.Init(appInstance.appHandle, MAKEINTRESOURCE(IDI_AUDIOPLAYER));
    newWindowConfig.smallAppIcon_.Init(appInstance.appHandle, MAKEINTRESOURCE(IDI_MONKEY_ICON));
    newWindowConfig.mouseCursor_.Init(appInstance.appHandle, MAKEINTRESOURCE(IDC_DARK_OXYGEN_CURSOR_NORMAL));
    
    SetWindowConfig(newWindowConfig);

    initResult = App::Init(appInstance, resourceManager);
    if (initResult.HasErrors()) {
        initResult.AppendError("AudioPlayerApp::Init() : Error initialising base element.");
        return initResult;
    }

    initResult = userInputHandler_.Init(this, &inputManager_);
    if (initResult.HasErrors()) {
        initResult.AppendError("AudioPlayerApp::Init() : Error initialising user input handler.");
        return initResult;
    }

    SetUserInputHandler(&userInputHandler_);

    initResult = SelectNextScene();
    if (initResult.HasErrors()) {
        initResult.AppendError("AudioPlayerApp::Init() : Error selecting first scene.");
    }

    return initResult;
}

Result AudioPlayerApp::SelectNextScene() {
    if (currentScene_ == nullptr) {
        currentScene_ = &scene1_;
    } else if (currentScene_ == &scene1_) {
        currentScene_ = &scene2_;
    } else if (currentScene_ == &scene2_) {
        currentScene_ = &scene3_;
    } else if (currentScene_ == &scene3_) {
        currentScene_ = &scene1_;
    }
    return SelectScene(currentScene_);
}

void AudioPlayerApp::ShowSettings() {
    PushScene(&scene3_);
}

void AudioPlayerApp::HideSettings() {
    PopScene();
}
