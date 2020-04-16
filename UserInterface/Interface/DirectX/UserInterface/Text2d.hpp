#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/DirectXInterface.hpp>
#include <UserInterface/Element.hpp>

class Text;

class Text2d : public Element {

public:
    Text2d() = default;
    virtual ~Text2d() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;
    void RenderText(const double& dt, const std::string& text);

public:
    void SetStyle(const char* styleName);
    void SetText(const std::string& newText);
//
//private:
//    Result UpdateDetails();

private:
    const char* styleName_;
    std::string text_;
    Text* textToDraw_;
};
