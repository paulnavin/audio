#pragma once

#include "Model3d.hpp"
#include "StlWrapper.hpp"

class ModelTriangle : public Model3d {
public:
    ModelTriangle() = default;
    ~ModelTriangle() = default;

public:
    virtual Result Init() {
        triangleVertices[0] = Vertex{ 0.0f, 0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        triangleVertices[1] = Vertex{ 0.11f, -0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        triangleVertices[2] = Vertex{ -0.11f, -0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        return Result{};
    }

public:
    virtual const size_t GetVertexCount() const {
        return 3;
    }
    virtual const uint8_t* GetVertexData() const {
        return reinterpret_cast<const uint8_t*>(triangleVertices.data());
    }
    virtual const VertexType GetVertexType() const {
        return VertexType::Triangle;
    }

private:
    std::array<Vertex, 3> triangleVertices;
};

