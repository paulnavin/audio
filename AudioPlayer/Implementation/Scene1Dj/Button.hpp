#pragma once

#include <Graphics/Element.hpp>
#include <Graphics/Rectangle2d.hpp>

class GraphicsEngine;

class Button : public Element {
public:
    Button() = default;
    virtual ~Button() = default;

public:
    Result Init(const GraphicsEngine& gfx) override;
    bool OnClick() override;

private:
    Rectangle2d background_;
};
