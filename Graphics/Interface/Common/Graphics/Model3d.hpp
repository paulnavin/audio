#pragma once

#include <Graphics/Vertex.hpp>
#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

enum class VertexType {
    Point,
    Line,
    Triangle,
};

class Model3d {
public:
    Model3d() = default;
    virtual ~Model3d() = default;

public:
    virtual const size_t GetVertexCount() const = 0;
    virtual const uint8_t* GetVertexData() const = 0;
    virtual const VertexType GetVertexType() const = 0;

public:
    virtual Result Init() = 0;
};
