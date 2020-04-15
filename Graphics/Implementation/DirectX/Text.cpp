#include <Graphics/Text.hpp>

#include <Display/ErrorDisplay.hpp>

#include <Graphics/Dimension2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>
#include <Graphics/TextResource.hpp>

Result Text::Init(GraphicsEngine* gfx, TextResource* resource) {
    resource->Init(gfx);
}

void Text::Render() {
    textResource_->Render();
}

void Text::SetText(const std::string& newText) {
    textResource_->SetText(newText);
}

void Text::SetPosition(const Position2d& position) {
    textResource_->SetPosition(position);
}

void Text::SetDimensions(const Dimension2d& dimensions) {
    textResource_->SetDimensions(dimensions);
}
