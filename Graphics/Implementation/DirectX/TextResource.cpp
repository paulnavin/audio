#include <Graphics/TextResource.hpp>

#include <Display/ErrorDisplay.hpp>
#include <Graphics/Dimension2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Position2d.hpp>

Result TextResource::Init(GraphicsEngine* gfx/*, const char* fontName*/) {
    const TextManager2d& textManager = gfx->GetTextManager2d();

    // TODO: Set up the text format and brush based on input style.
    textFormat_ = textManager.GetFpsTextFormat();
    brush_ = textManager.GetFpsBrush();

    return Result{};
}

Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> TextResource::GetBrush() {
    return brush_;
}
Microsoft::WRL::ComPtr<IDWriteTextFormat> TextResource::GetTextFormat() {
    return textFormat_;
}
