#pragma once

#include <Ui/Result.hpp>
#include <Ui/StlWrapper.hpp>

class Engine2d;

class Model2d {
public:
    Model2d() = default;
    virtual ~Model2d() = default;

public:
    virtual Result Init(const Engine2d& engine) = 0;

    // Note: No Result passing in Render, for performance reasons.
    virtual void Render() = 0;

    virtual void SetFps(const int64_t& newFps) = 0;
    virtual void SetShowFps(const bool show) = 0;
};
