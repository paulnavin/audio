#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

class GraphicsEngine;

class DjWaveform : public Element {
public:
    DjWaveform() = default;
    virtual ~DjWaveform() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override;

private:
    Rectangle2d window_;
};

