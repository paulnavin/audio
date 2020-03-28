#pragma once

#include <Graphics/Model3d.hpp>
#include <Stl/StlWrapper.hpp>

class ModelTriangle : public Model3d {
public:
    ModelTriangle() = default;
    ~ModelTriangle() = default;

public:
    Result Init() override {
        triangleVertices[0] = Vertex{ 0.0f, 0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        triangleVertices[1] = Vertex{ 0.11f, -0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        triangleVertices[2] = Vertex{ -0.11f, -0.1f, 0.3f, 1.0f, 1.0f, 0.0f, 1.0f };
        return Result{};
    }

public:
    const size_t GetVertexCount() const override {
        return 3;
    }
    const uint8_t* GetVertexData() const override {
        return reinterpret_cast<const uint8_t*>(triangleVertices.data());
    }
    const VertexType GetVertexType() const override {
        return VertexType::Triangle;
    }

private:
    std::array<Vertex, 3> triangleVertices;
};

