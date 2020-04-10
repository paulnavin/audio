#include "ViewSelectionGroup.hpp"

#include <Graphics/GraphicsEngine.hpp>
#include <Resources/ResourceManager.hpp>

Result ViewSelectionGroup::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionGroup::Init() : Error initialising base Element.");
        return initResult;
    }

    volumeButton_.SetParent(this);
    volumeButton_.SetPositionAsPercentage(0.0f, 0.0f);
    volumeButton_.SetDimensionsAsPercentage(25.0f, 100.0f);
    volumeButton_.SetText("VOL");
    initResult = volumeButton_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionGroup::Init() : Error initialising volume button.");
        return initResult;
    }

    tempoButton_.SetParent(this);
    tempoButton_.SetPositionAsPercentage(25.0f, 0.0f);
    tempoButton_.SetDimensionsAsPercentage(25.0f, 100.0f);
    tempoButton_.SetText("TEMPO");
    initResult = tempoButton_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionGroup::Init() : Error initialising tempo button.");
        return initResult;
    }

    fxButton_.SetParent(this);
    fxButton_.SetPositionAsPercentage(50.0f, 0.0f);
    fxButton_.SetDimensionsAsPercentage(25.0f, 100.0f);
    fxButton_.SetText("FX");
    initResult = fxButton_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionGroup::Init() : Error initialising FX button.");
        return initResult;
    }

    loopButton_.SetParent(this);
    loopButton_.SetPositionAsPercentage(75.0f, 0.0f);
    loopButton_.SetDimensionsAsPercentage(25.0f, 100.0f);
    loopButton_.SetText("LOOP");
    initResult = loopButton_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ViewSelectionGroup::Init() : Error initialising loop button.");
        return initResult;
    }

    AddChild(&volumeButton_);
    AddChild(&tempoButton_);
    AddChild(&fxButton_);
    AddChild(&loopButton_);

    return initResult;
}
