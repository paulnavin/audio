#pragma once

#include <Platform/ErrorHandling.hpp>
#include <Graphics/TextStyle.hpp>
#include <UserInterface/Element.hpp>

class Text;

class Text2d : public Element {

public:
    Text2d() = default;
    virtual ~Text2d() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;
    void RenderText(const double& dt, const char* text);

public:
    void SetStyle(const TextStyle::Id styleId);
    void SetText(const char* newText);

private:
    static constexpr size_t MAX_TEXT_LENGTH = 100;

private:
    TextStyle::Id styleId_;
    char text_[MAX_TEXT_LENGTH];
    Text* textToDraw_;
};
