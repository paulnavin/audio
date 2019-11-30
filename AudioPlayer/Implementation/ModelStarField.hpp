#pragma once

#include "Model3d.hpp"
#include "StlWrapper.hpp"

class ModelStarField : public Model3d {
public:
    ModelStarField() = default;
    ~ModelStarField() = default;

public:
    virtual Result Init() {
        for (size_t i = 0; i < STAR_FIELD_SIZE; ++i) {
            starField_[i].x = randomPosition();
            starField_[i].y = randomPosition();
            starField_[i].z = randomPosition();
            starField_[i].red = randomColour();
            starField_[i].green = randomColour();
            starField_[i].blue = randomColour();
        }
        return Result{};
    }

public:
    virtual const size_t GetVertexCount() const {
        return starField_.size();
    }
    virtual const uint8_t* GetVertexData() const {
        return reinterpret_cast<const uint8_t*>(starField_.data());
    }
    virtual const VertexType GetVertexType() const {
        return VertexType::Point;
    }

private:
    static inline float randomColour() {
        return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
    }

    // function to create a "random" float between -1.0f and 1.0f
    static inline float randomPosition() {
        return  static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * 2 - 1;
    }

private:
    // TODO: Move this stuff out of the Engine, into the App.
    static constexpr size_t STAR_FIELD_SIZE = 1000;
    std::array<Vertex, STAR_FIELD_SIZE> starField_;
};
