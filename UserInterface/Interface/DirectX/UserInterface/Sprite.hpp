#pragma once

#include <ErrorHandling/Result.hpp>
#include <UserInterface/Element.hpp>

class Bitmap;

class Sprite : public Element {

public:
    Sprite() = default;
    virtual ~Sprite() = default;

public:
    Result Init(ModelPortal* portal) override;
    void Render(const double& dt) override;

public:
    void SetBitmapName(const char* name);

protected:
    Bitmap* bitmapToDraw_;
    const char*     name_;
};
