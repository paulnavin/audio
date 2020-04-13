#pragma once

#include <Stl/StlWrapper.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

struct ModelPortal;

class Button : public Element {
public:
    Button() = default;
    virtual ~Button();

public:
    Result Init(ModelPortal* portal) override;
    bool OnClick() override;
    void HandleCommand(const Command::Id& command) override;
    void HandleMouseMove(const float& x, const float& y) override;
    
    void SetOnClickHandler(std::function<void()> onClickHandler);

private:
    Rectangle2d background_;
    Rectangle2d buttonDownHighlight_;
    bool mouseOver_ = false;
    bool buttonDownOnThisButton_ = false;
    Rectangle2d mouseOverHighlight_;
    std::function<void()> onClickHandler_;
};
