#pragma once

#include <Ui/Engine2d.hpp>
#include <Ui/Ellipse2d.hpp>
#include <Ui/Model2d.hpp>
#include <Ui/Rectangle2d.hpp>
#include <Ui/StlWrapper.hpp>
#include <Ui/Text2d.hpp>

class ModelBasic2d : public Model2d {
public:
    ModelBasic2d() = default;
    ~ModelBasic2d() = default;

public:
    virtual Result Init(const Engine2d& engine) override {
        Result initResult = rectangle_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        rectangle_.SetColour(Colour{ 1.0f, 0.0f, 1.0f, 1.0f });

        initResult = ellipse_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D ellipse.");
            return initResult;
        }
        ellipse_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 1.0f });

        initResult = fpsText_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("Window::Init() : Error initialising 2D FPS text.");
            return initResult;
        }

        showFpsText_ = true;

        return Result{};
    }

    void Render() {
        ellipse_.Render();
        rectangle_.Render();
        fpsText_.Render();
    }

    void SetFps(const int64_t& newFps) override {
        std::wostringstream fpsString{};
        fpsString.precision(6);
        fpsString << "FPS: " << newFps << std::endl;

        fpsText_.SetText(fpsString.str());
    }

    void SetShowFps(const bool show) override {
        showFpsText_ = show;
    }

private:
    Ellipse2d ellipse_;
    Rectangle2d rectangle_;
    Text2d fpsText_;
    bool showFpsText_;
};

