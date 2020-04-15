#include <UserInterface/Text2d.hpp>

#include <Graphics/Text.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Text2d::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Text2d::Init() : Couldn't init base element.");
        return initResult;
    }

    ResourceManager* resourceManager = portal->resourceManager;
    textToDraw_ = resourceManager->GimmeSomeTextDammit(styleName_);
    if (textToDraw_ == nullptr) {
        initResult.AppendError("Text2d::Init() : Couldn't get text style.");
        initResult.AppendError(styleName_);
        return initResult;
    }

    textToDraw_->SetText(text_);
    textToDraw_->SetPosition(positionOnScreen_);
    textToDraw_->SetDimensions(dimensionsOnScreen_);

    return initResult;
}

void Text2d::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);

    textToDraw_->Render();
}

void Text2d::SetStyle(const char* styleName) {
    styleName_ = styleName;
}

void Text2d::SetText(const std::string& text) {
    text_ = text;
}
