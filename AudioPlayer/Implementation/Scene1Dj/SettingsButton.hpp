#pragma once

#include <UserInterface/Element.hpp>

#include "Button.hpp"

struct ModelPortal;

// TODO: Is this class really needed?
class SettingsButton : public Element {
public:
    SettingsButton() = default;
    virtual ~SettingsButton() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

private:
    Button button_;
};
