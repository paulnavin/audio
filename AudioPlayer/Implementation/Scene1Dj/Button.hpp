#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

struct ModelPortal;

class Button : public Element {
public:
    Button() = default;
    virtual ~Button() = default;

public:
    Result Init(ModelPortal* portal) override;
    bool OnClick() override;

private:
    Rectangle2d background_;
};
