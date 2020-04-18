#include <UserInterface/Text2d.hpp>

#include <Graphics/DirectXInterface.hpp>
#include <Graphics/Text.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Text2d::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Text2d::Init() : Couldn't init base element.");
        return initResult;
    }

    ResourceManager* resourceManager = portal->resourceManager;
    textToDraw_ = resourceManager->GimmeATextBoxDammit(styleId_);
    if (textToDraw_ == nullptr) {
        initResult.AppendError("Text2d::Init() : Couldn't get text style.");
        return initResult;
    }

    textToDraw_->SetPosition(positionOnScreen_);
    textToDraw_->SetDimensions(dimensionsOnScreen_);
    textToDraw_->SetText(text_);

    return initResult;
}

void Text2d::Render(const double& dt) {
    UNREFERENCED_PARAMETER(dt);

    textToDraw_->Render();
}

void Text2d::RenderText(const double& dt, const std::string& text) {
    UNREFERENCED_PARAMETER(dt);
    UNREFERENCED_PARAMETER(text);

    textToDraw_->RenderText(text);
}

void Text2d::SetStyle(const TextStyle::Id styleId) {
    styleId_ = styleId;
}

void Text2d::SetText(const std::string& text) {
    text_ = text;
}
