#include "ModelDj.hpp"

#include <Graphics/GraphicsEngine.hpp>

Result DjTopRow::Init(const GraphicsEngine& gfx) {
    Result initResult = Element::Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    openFile1Button_.SetParent(this);
    openFile1Button_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    openFile1Button_.SetPosition(0.0f, 0.0f);
    openFile1Button_.SetDimensionsAsPercentage(11.5f, 100.0f);
    initResult = openFile1Button_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising open file button 1.");
        return initResult;
    }

    openFile2Button_.SetParent(this);
    openFile2Button_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    openFile2Button_.SetDimensionsAsPercentage(11.5f, 100.0f);
    openFile2Button_.SetPositionAsPercentage(-11.5f, 0.0f);
    initResult = openFile2Button_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising open file button 2.");
        return initResult;
    }

    waveform1_.SetParent(this);
    waveform1_.SetPositionAsPercentage(11.5f, 0.0f);
    waveform1_.SetDimensionsAsPercentage(38.5f, 100.0f);
    initResult = waveform1_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising waveform 1.");
        return initResult;
    }

    waveform2_.SetParent(this);
    waveform2_.SetPositionAsPercentage(50.0f, 0.0f);
    waveform2_.SetDimensionsAsPercentage(38.5f, 100.0f);
    initResult = waveform2_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising waveform 2.");
        return initResult;
    }

    AddChild(&openFile1Button_);
    AddChild(&openFile2Button_);
    AddChild(&waveform1_);
    AddChild(&waveform2_);

    return initResult;
}
