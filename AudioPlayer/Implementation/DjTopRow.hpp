#pragma once

#include <Graphics/Element.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Rectangle2d.hpp>

#include "ExplosionAnimation.hpp"
#include "JogWheel.hpp"

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
};

