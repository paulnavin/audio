#pragma once

#include <Graphics/Element.hpp>
#include <Graphics/Rectangle2d.hpp>

#include "DjWaveform.hpp"

class GraphicsEngine;

class DjTopRow : public Element {
public:
    DjTopRow() = default;
    virtual ~DjTopRow() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;

private:
    Rectangle2d openFile1Button_;
    Rectangle2d openFile2Button_;
    DjWaveform waveform1_;
    DjWaveform waveform2_;
};
