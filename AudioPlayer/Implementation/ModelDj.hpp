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
    ModelDj()
        : Model2d()
        , jogWheel1_(nullptr)
        , openFile1Button_(nullptr)
        , openFile2Button_(nullptr)
        , fpsText_(nullptr)
        , mousePositionText_(nullptr) {};
    ~ModelDj() = default;

public:
    virtual Result Init(const Engine2d& engine, const TextManager2d& textManager) override {
        Result initResult = openFile1Button_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        openFile1Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile1Button_.SetPosition(0.0f, 0.0f);
        openFile1Button_.SetDimensions(50.0f, 50.0f);

        initResult = openFile2Button_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D rectangle.");
            return initResult;
        }
        openFile2Button_.SetColour(Colour{ 0.5f, 0.5f, 0.5f, 1.0f });
        openFile2Button_.SetPosition(900.0f, 0.0f);
        openFile2Button_.SetDimensions(50.0f, 50.0f);

        initResult = jogWheel1_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D jog wheel.");
            return initResult;
        }
        jogWheel1_.SetSlipmatColour(Colour{ 1.0f, 0.5f, 0.5f, 1.0f });
        jogWheel1_.SetPositionColour(Colour{ 0.0f, 0.0f, 0.6f, 1.0f });
        jogWheel1_.SetPosition(181.0f, 225.0f);  // Note: This doesn't match the JogWheel code, cos for click detection need origin at top left.
        jogWheel1_.SetDimensions(150.0f, 150.0f);

        initResult = fpsText_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D FPS text.");
            return initResult;
        }
        fpsText_.SetPosition(5.0f, 5.0f);
        fpsText_.SetDimensions(20.0f, 100.0f);

        showFps_ = true;

        initResult = mousePositionText_.Init(engine, textManager);
        if (initResult.HasErrors()) {
            initResult.AppendError("ModelDj::Init() : Error initialising 2D mouse position text.");
            return initResult;
        }

        mousePositionText_.SetPosition(5.0f, 35.0f);
        mousePositionText_.SetDimensions(20.0f, 100.0f);

        showMousePosition_ = true;

        elements_.insert(&jogWheel1_);
        elements_.insert(&openFile1Button_);
        elements_.insert(&openFile2Button_);

        SetFpsElement(&fpsText_);
        SetMousePositionElement(&mousePositionText_);

        return Result{};
    }

    void Update(const double& dt) override {
        jogWheel1_.Update(dt);
    }

    void SetFps(const int64_t& newFps) override {
        Model2d::SetFps(newFps);

        std::wostringstream fpsString{};
        fpsString.precision(6);
        fpsString << "FPS: " << fps_ << std::endl;

        fpsText_.SetText(fpsString.str());
    }

    void SetMousePosition(const float& x, const float& y) override {
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

