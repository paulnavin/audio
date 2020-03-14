#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/Ellipse2d.hpp>
#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Rectangle2d.hpp>

class ModelBasic2d : public Model2d {
public:
    explicit ModelBasic2d()
        : Model2d()
        , ellipse_(nullptr)
        , rectangle_(nullptr) {};
    ~ModelBasic2d() = default;

public:
    virtual Result Init(const GraphicsEngine& gfx) override {
        Result initResult = rectangle_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        rectangle_.SetColour(Colour{ 1.0f, 0.0f, 1.0f, 1.0f });
        rectangle_.SetPosition(300.0f, 300.0f);
        rectangle_.SetDimensions(50.0f, 50.0f);

        initResult = ellipse_.Init(gfx);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D ellipse.");
            return initResult;
        }
        ellipse_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
        ellipse_.SetPosition(700.0f, 500.0f);
        ellipse_.SetDimensions(75.0f, 200.0f);

        elements_.insert(&ellipse_);
        elements_.insert(&rectangle_);

        return Model2d::Init(gfx);
    }

private:
    Ellipse2d ellipse_;
    Rectangle2d rectangle_;
};

