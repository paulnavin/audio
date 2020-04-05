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
    void HandleCommand(const Command::Id& command) override;
    void HandleMouseMove(const float& x, const float& y) override;
    
    void SetOnClickHandler();

private:
    Rectangle2d background_;
    Rectangle2d buttonDownHighlight_;
    bool mouseOver_ = false;
    Rectangle2d mouseOverHighlight_;
};
