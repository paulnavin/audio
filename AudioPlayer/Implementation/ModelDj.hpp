#pragma once

#include <Graphics/Engine2d.hpp>
#include <Graphics/Ellipse2d.hpp>
#include <Graphics/Model2d.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Utility/StlWrapper.hpp>

#include "JogWheel.hpp"

class ModelDj : public Model2d {
public:
    ModelDj() = default;
    ~ModelDj() = default;

public:
    virtual Result Init(const Engine2d& engine) override {
        Result initResult = openFile1Button_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        openFile1Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile1Button_.SetDimensions(0.0f, 0.0f, 50.0f, 50.0f);

        initResult = openFile2Button_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        openFile2Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile2Button_.SetDimensions(900.0f, 0.0f, 50.0f, 50.0f);

        initResult = jogWheel1_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D jog wheel.");
            return initResult;
        }
        jogWheel1_.SetSlipmatColour(Colour{ 1.0f, 0.5f, 0.5f, 1.0f });
        jogWheel1_.SetPositionColour(Colour{ 0.0f, 0.0f, 0.6f, 1.0f });

        initResult = fpsText_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D FPS text.");
            return initResult;
        }

        showFps_ = true;

        initResult = mousePositionText_.Init(engine);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D mouse position text.");
            return initResult;
        }

        initResult = mousePositionText_.SetPosition(5.0f, 35.0f);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D mouse position text.");
            return initResult;
        }

        showMousePosition_ = true;

        return Result{};
    }

    void Update(const double& dt) override {
        jogWheel1_.Update(dt);
    }

    void Render(const double& dt) override {
        openFile1Button_.Render();
        openFile2Button_.Render();
        jogWheel1_.Render(dt);

        if (showFps_ == true) {
            fpsText_.Render();
        }

        if (showMousePosition_ == true) {
            mousePositionText_.Render();
        }
    }

    void SetFps(const int64_t& newFps) override {
        Model2d::SetFps(newFps);

        std::wostringstream fpsString{};
        fpsString.precision(6);
        fpsString << "FPS: " << fps_ << std::endl;

        fpsText_.SetText(fpsString.str());
    }

    void SetMousePosition(const int32_t& x, const int32_t& y) override {
        Model2d::SetMousePosition(x, y);

        std::wostringstream outputString{};
        outputString.precision(6);
        outputString << "Mouse: " << x << ", " << y << std::endl;

        mousePositionText_.SetText(outputString.str());
    }

private:
    JogWheel jogWheel1_;
    Rectangle2d openFile1Button_;
    Rectangle2d openFile2Button_;

    Text2d fpsText_;
    Text2d mousePositionText_;
};

