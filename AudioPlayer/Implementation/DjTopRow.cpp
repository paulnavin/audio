#include "ModelDj.hpp"

#include <Graphics/AnimatedSprite.hpp>
#include <Graphics/Engine2d.hpp>
#include <Graphics/Ellipse2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <UserInterface/Window.hpp>

Result DjTopRow::Init(const GraphicsEngine& gfx) {
    Result initResult = Element::Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising base Element.");
        return initResult;
    }

    openFile1Button_.SetParent(this);
    openFile1Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    openFile1Button_.SetPosition(0.0f, 0.0f);
    openFile1Button_.SetDimensionsAsPercentage(10.0f, 100.0f);
    initResult = openFile1Button_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising open file button 1.");
        return initResult;
    }

    openFile2Button_.SetParent(this);
    openFile2Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
    openFile2Button_.SetDimensionsAsPercentage(10.0f, 100.0f);
    openFile2Button_.SetPositionAsPercentage(-10.0f, 0.0f);
    initResult = openFile2Button_.Init(gfx);
    if (initResult.HasErrors()) {
        initResult.AppendError("DjTopRow::Init() : Error initialising open file button 2.");
        return initResult;
    }

    AddChild(&openFile1Button_);
    AddChild(&openFile2Button_);

    return initResult;
}
