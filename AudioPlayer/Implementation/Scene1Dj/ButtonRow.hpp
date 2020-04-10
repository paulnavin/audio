#pragma once

#include <UserInterface/Element.hpp>

#include "ViewSelectionButton.hpp"
#include "ViewSelectionGroup.hpp"
#include "SettingsButton.hpp"

struct ModelPortal;

class ButtonRow : public Element {
public:
    ButtonRow() = default;
    virtual ~ButtonRow() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

private:
    ViewSelectionGroup selectionGroup1_;
    ViewSelectionGroup selectionGroup2_;
    SettingsButton settings_;
};
