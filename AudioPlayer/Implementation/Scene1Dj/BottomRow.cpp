#include "BottomRow.hpp"

#include <Graphics/GraphicsEngine.hpp>

Result BottomRow::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    cueButton1_.SetParent(this);
    cueButton1_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    cueButton1_.SetPosition(0.0f, 0.0f);
    cueButton1_.SetDimensionsAsPercentage(11.5f, 100.0f);
    initResult = cueButton1_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising cue button 1.");
        return initResult;
    }

    cueButton2_.SetParent(this);
    cueButton2_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    cueButton2_.SetDimensionsAsPercentage(11.5f, 100.0f);
    cueButton2_.SetPositionAsPercentage(-23.0f, 0.0f);
    initResult = cueButton2_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising cue button 2.");
        return initResult;
    }

    playButton1_.SetParent(this);
    playButton1_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    playButton1_.SetDimensionsAsPercentage(11.5f, 100.0f);
    playButton1_.SetPositionAsPercentage(11.5f, 0.0f);
    initResult = playButton1_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising play button 1.");
        return initResult;
    }

    playButton2_.SetParent(this);
    playButton2_.SetHighlightColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    playButton2_.SetDimensionsAsPercentage(11.5f, 100.0f);
    playButton2_.SetPositionAsPercentage(-11.5f, 0.0f);
    initResult = playButton2_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising play button 2.");
        return initResult;
    }

    AddChild(&cueButton1_);
    AddChild(&cueButton2_);
    AddChild(&playButton1_);
    AddChild(&playButton2_);

    return initResult;
}
