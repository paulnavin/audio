#pragma once

#include <Graphics/Dimension2d.hpp>
#include <Graphics/Position2d.hpp>
#include <Platform/ErrorHandling.hpp>
#include <Platform/Minion.hpp>
#include <UserInput/Command.hpp>

struct ModelPortal;

class Element : public Minion {
public:
    Element() = default;
    virtual ~Element() = default;

public:
    virtual Result Init(ModelPortal* portal);

    // Note: No Result passing in Render, for performance reasons.
    // By default just renders all children.
    virtual void Render(const double& dt);

    // Note: By default checks children for clicking.
    virtual bool OnClick();

    const bool IsEnabled() const override;

public:
    const Position2d& GetPosition() const;
    const Position2d& GetAbsolutePosition() const;
    const Dimension2d& GetDimensions() const;
    const bool IsInitialised() const;

public:
    void AddChild(Element* newChild);
    // TODO: Remove OnMouseClicked when clicking is handled by events.
    void OnMouseClicked(const float& x, const float& y);
    void SetDimensions(const float& widthInPixels, const float& heightInPixels);
    void SetParent(const Element* parent);
    void SetPosition(const float& newX, const float& newY);
    void SetPositionAsPercentage(const float& newX, const float& newY);
    void SetDimensionsAsPercentage(const float& width, const float& height); // From 0 to 100.
    void SetEnabled(const bool& enabled);

protected:
    ModelPortal* chell_;
    Dimension2d dimensionsOnScreen_;
    bool isEnabled_ = true;
    const Element* parent_;
    Position2d  positionOnScreen_;

private:
    static constexpr size_t MAX_CHILD_COUNT = 20;

private:
    void UpdateDimensionsOnScreen();
    void UpdatePositionOnScreen();

private:
    Element*    children_[MAX_CHILD_COUNT];
    size_t      childCount_ = 0;
    bool        isInitialised_ = false;
    Position2d  position_;
    Position2d  positionAsPercentage_;
    bool        percentagePosition_ = false;
    Dimension2d dimensions_;
    bool        percentageDimensions_ = false;
};
