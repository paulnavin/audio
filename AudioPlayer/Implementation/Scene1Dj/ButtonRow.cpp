#include "ButtonRow.hpp"

#include <Graphics/GraphicsEngine.hpp>

Result ButtonRow::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ButtonRow::Init() : Error initialising base Element.");
        return initResult;
    }

    selectionGroup1_.SetParent(this);
    selectionGroup1_.SetPosition(0.0f, 0.0f);
    selectionGroup1_.SetDimensionsAsPercentage(46.0f, 100.0f);
    initResult = selectionGroup1_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ButtonRow::Init() : Error initialising selection group 1.");
        return initResult;
    }

    selectionGroup2_.SetParent(this);
    selectionGroup2_.SetDimensionsAsPercentage(46.0f, 100.0f);
    selectionGroup2_.SetPositionAsPercentage(-46.0f, 0.0f);
    initResult = selectionGroup2_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ButtonRow::Init() : Error initialising selection group 2.");
        return initResult;
    }

    settings_.SetParent(this);
    settings_.SetDimensionsAsPercentage(8.0f, 100.0f);
    settings_.SetPositionAsPercentage(46.0f, 0.0f);
    initResult = settings_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("ButtonRow::Init() : Error initialising settings button.");
        return initResult;
    }

    AddChild(&selectionGroup1_);
    AddChild(&selectionGroup2_);
    AddChild(&settings_);

    return initResult;
}
