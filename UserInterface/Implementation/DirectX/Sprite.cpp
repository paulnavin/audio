#include <UserInterface/Sprite.hpp>

#include <Graphics/BitmapResource.hpp>
#include <Graphics/Position2d.hpp>
#include <Resources/ResourceManager.hpp>
#include <UserInterface/ModelPortal.hpp>

Result Sprite::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Sprite::Init() : Couldn't init base element.");
        return initResult;
    }

    ResourceManager* resourceManager = portal->resourceManager;
    bitmapToDraw_ = resourceManager->GimmeABitmapDammit(name_);
    if (bitmapToDraw_ == nullptr) {
        initResult.AppendError("Sprite::Init() : Couldn't get bitmap.");
        initResult.AppendError(name_);
        return initResult;
    }
    return initResult;
}

void Sprite::Render(const double&) {
    bitmapToDraw_->Render(positionOnScreen_, dimensionsOnScreen_);
}

void Sprite::SetBitmapName(const char* name) {
    name_ = name;
}
