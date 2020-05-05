#pragma once

#include <Platform/ErrorHandling.hpp>
#include <UserInterface/DebugInfo.hpp>
#include <UserInterface/Sprite.hpp>

class Element;
class Window;

struct ModelPortal;

class Model2d {
public:
    Model2d();
    virtual ~Model2d() = default;

public:
    virtual Result Init(ModelPortal* portal);
    virtual void Update(const double& dt);
    void Render(const double& dt);

    void AddChildElement(Element* newChild);

    void SetActive(bool isActive);
    void SetCursorBitmap(const char* bitmapName);
    void SetFps(const int64_t& newFps);
    void SetMousePosition(const float& x, const float& y);
    void SetWindow(Window* window);
    void ToggleDebugInfo();

private:
    static constexpr size_t MAX_ELEMENT_COUNT = 20;
    
private:
    Element* elements_[MAX_ELEMENT_COUNT];
    size_t elementCount_ = 0;

    float mouseXPosition_;
    float mouseYPosition_;
    Sprite mouseCursor_;
    const char* mouseCursorBitmapName_;

    bool showDebugInfo_;
    DebugInfo debugElement_;

    Window* window_;

    bool isActive_ = true;
};
