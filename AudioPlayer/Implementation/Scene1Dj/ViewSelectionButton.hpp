#pragma once

#include <UserInterface/Button.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/Text2d.hpp>

struct ModelPortal;

class ViewSelectionButton : public Element {
public:
    ViewSelectionButton() = default;
    virtual ~ViewSelectionButton() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

public:
    Result SetText(const std::string& text);

private:
    Button button_;
    Text2d text_;
};
