#pragma once

#include <UserInterface/Element.hpp>

#include "HighlightButton.hpp"

struct ModelPortal;

class BottomRow : public Element {
public:
    BottomRow() = default;
    ~BottomRow() = default;

public:
    Result Init(ModelPortal* portal) override;

private:
    HighlightButton cueButton1_;
    HighlightButton cueButton2_;
    HighlightButton playButton1_;
    HighlightButton playButton2_;
};
