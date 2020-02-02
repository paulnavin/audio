#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/Ellipse2d.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Utility/StlWrapper.hpp>

class ModelBasic2d : public Model2d {
public:
    explicit ModelBasic2d() : Model2d(), ellipse_(nullptr), rectangle_(nullptr), fpsText_(nullptr) {};
    ~ModelBasic2d() = default;

public:
    virtual Result Init(const Engine2d& engine, const TextManager2d& textManager) override {
        Result initResult = rectangle_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        rectangle_.SetColour(Colour{ 1.0f, 0.0f, 1.0f, 1.0f });
        rectangle_.SetPosition(300.0f, 300.0f);
        rectangle_.SetDimensions(50.0f, 50.0f);

        initResult = ellipse_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D ellipse.");
            return initResult;
        }
        ellipse_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });
        ellipse_.SetPosition(700.0f, 500.0f);
        ellipse_.SetDimensions(75.0f, 200.0f);

        initResult = fpsText_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D FPS text.");
            return initResult;
        }

        showFps_ = true;

        elements_.insert(&ellipse_);
        elements_.insert(&rectangle_);

        SetFpsElement(&fpsText_);

        return Result{};
    }

    void Update(const double& dt) override {
        UNREFERENCED_PARAMETER(dt);
    }

    void SetFps(const int64_t& newFps) override {
        Model2d::SetFps(newFps);

        std::wostringstream fpsString{};
        fpsString.precision(6);
        fpsString << "FPS: " << fps_ << std::endl;

        fpsText_.SetText(fpsString.str());
    }

private:
    Ellipse2d ellipse_;
    Rectangle2d rectangle_;
    Text2d fpsText_;
};

