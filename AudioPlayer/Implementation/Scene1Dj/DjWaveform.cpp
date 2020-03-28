#include "DjWaveform.hpp"

#include <Graphics/GraphicsEngine.hpp>

Result DjWaveform::Init(const GraphicsEngine& gfx) {
    Result initResult = Element::Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjWaveform::Init() : Error initialising base Element.");
        return initResult;
    }

    window_.SetParent(this);
    window_.SetColour(Colour{ 0.1f, 0.1f, 0.5f, 1.0f });
    window_.SetDimensionsAsPercentage(100.0f, 100.0f);
    window_.SetPositionAsPercentage(0.0f, 0.0f);
    initResult = window_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjWaveform::Init() : Error initialising window.");
        return initResult;
    }

    AddChild(&window_);

    return initResult;
}
