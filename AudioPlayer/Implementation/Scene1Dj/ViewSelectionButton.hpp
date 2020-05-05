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
    Result SetText(const char* text);

private:
    static constexpr size_t MAX_STRING_LENGTH = 100;
private:
    Button button_;
    Text2d text_;
    char textToShow_[MAX_STRING_LENGTH];
};
