#pragma once

#include <Platform/Stl.hpp>
#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>
#include <UserInterface/Sprite.hpp>

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
    void SetBackgroundImage(const char* name);
    void SetForegroundImage(const char* name);

private:
    Rectangle2d background_;
    Sprite backgroundImage_;
    Sprite foregroundImage_;
    Rectangle2d buttonDownHighlight_;
    bool mouseOver_ = false;
    bool buttonDownOnThisButton_ = false;
    Rectangle2d mouseOverHighlight_;
    std::function<void()> onClickHandler_;
    const char* backgroundImageName_;
    const char* foregroundImageName_;
};
