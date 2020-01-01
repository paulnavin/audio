#pragma once

#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

class Engine2d;

class Model2d {
public:
    Model2d() = default;
    virtual ~Model2d() = default;

public:
    virtual Result Init(const Engine2d& engine) = 0;

    virtual void Update(const double& dt) = 0;

    // Note: No Result passing in Render, for performance reasons.
    virtual void Render(const double& dt) = 0;

    virtual void SetFps(const int64_t& newFps);
    virtual void SetShowFps(const bool show);

    virtual void SetMousePosition(const int32_t& x, const int32_t& y);
    virtual void SetShowMousePosition(const bool show);

protected:
    bool showFps_;
    int64_t fps_;

    bool showMousePosition_;
    int32_t mouseXPosition_;
    int32_t mouseYPosition_;
};
