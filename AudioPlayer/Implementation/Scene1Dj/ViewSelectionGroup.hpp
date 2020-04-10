#pragma once

#include <UserInterface/Element.hpp>

#include "ViewSelectionButton.hpp"

struct ModelPortal;

class ViewSelectionGroup : public Element {
public:
    ViewSelectionGroup() = default;
    virtual ~ViewSelectionGroup() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

private:
    ViewSelectionButton volumeButton_;
    ViewSelectionButton tempoButton_;
    ViewSelectionButton fxButton_;
    ViewSelectionButton loopButton_;
};
