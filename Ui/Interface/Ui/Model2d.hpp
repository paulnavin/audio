#pragma once

#include <Ui/Result.hpp>
#include <Ui/StlWrapper.hpp>

class Model2d {
public:
    Model2d() = default;
    virtual ~Model2d() = default;

public:
    virtual Result Init() = 0;
    virtual void Render() const = 0;
};
