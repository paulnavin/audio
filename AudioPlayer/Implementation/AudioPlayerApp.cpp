#include "AudioPlayerApp.hpp"

#include <UserInterface/WindowConfig.hpp>
#include <ErrorHandling/Result.hpp>

#include "Scene1Dj.hpp"
#include "Scene2Basic.hpp"
#include "Resource.h"

Result AudioPlayerApp::Init(const HINSTANCE& appInstance, const ResourceManager& resourceManager) {
    Result initResult{};

    initResult = InitConfig("someRubbish.ini");
    if (initResult.HasErrors()) {
        initResult.AppendError("AudioPlayerApp::Init() : Error loading app config.");
        return initResult;
    }

    WindowConfig newWindowConfig{};
    newWindowConfig.height = config_.GetInt32("height", 200);
    newWindowConfig.width = config_.GetInt32("width", 300);
    newWindowConfig.showCursor_ = false;
    LoadString(appInstance, IDS_APP_TITLE, newWindowConfig.title.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    LoadString(appInstance, IDC_AUDIOPLAYER, newWindowConfig.mainWindowClassName_.data(), WindowConfig::MAX_RESOURCE_NAME_LENGTH);
    newWindowConfig.appIcon_.Init(appInstance, MAKEINTRESOURCE(IDI_AUDIOPLAYER));
    newWindowConfig.smallAppIcon_.Init(appInstance, MAKEINTRESOURCE(IDI_MONKEY_ICON));
    newWindowConfig.mouseCursor_.Init(appInstance, MAKEINTRESOURCE(IDC_DARK_OXYGEN_CURSOR_NORMAL));
    
    InitWindowConfig(newWindowConfig);

    scenes_[0] = new Scene1Dj();
    scenes_[1] = new Scene2Basic();

    return App::Init(appInstance, resourceManager);
}
