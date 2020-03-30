#pragma once

#include <ErrorHandling/Result.hpp>
#include <Graphics/Vertex.hpp>
#include <Graphics/VertexType.hpp>
#include <Stl/StlWrapper.hpp>

class Model3d {
public:
    Model3d() = default;
    virtual ~Model3d() = default;

public:
    virtual const size_t GetVertexCount() const = 0;
    virtual void* GetVertexData() = 0;
    virtual const VertexType GetVertexType() const = 0;

public:
    virtual Result Init() = 0;
};
