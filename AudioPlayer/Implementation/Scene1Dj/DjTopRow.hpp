#pragma once

#include <UserInterface/Element.hpp>

#include "DjButton.hpp"
#include "DjWaveform.hpp"

class GraphicsEngine;

class DjTopRow : public Element {
public:
    DjTopRow() = default;
    virtual ~DjTopRow() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;

private:
    DjButton openFile1Button_;
    DjButton openFile2Button_;
    DjWaveform waveform1_;
    DjWaveform waveform2_;
};
