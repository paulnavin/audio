#pragma once

#include <UserInterface/Model3d.hpp>
#include <Stl/StlWrapper.hpp>

class Model3dSettingsOverlay : public Model3d {
public:
    Model3dSettingsOverlay() = default;
    ~Model3dSettingsOverlay() = default;

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
    void* GetVertexData() override {
        return reinterpret_cast<void*>(triangleVertices.data());
    }
    const VertexType GetVertexType() const override {
        return VertexType::Triangle;
    }

private:
    std::array<Vertex, 3> triangleVertices;
};

