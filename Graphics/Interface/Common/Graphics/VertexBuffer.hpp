#pragma once

#include "VertexType.hpp"

struct VertexBuffer {
    VertexBuffer() = default;
    ~VertexBuffer() = default;

    void* data = nullptr;
    size_t size{};
    VertexType type = VertexType::Point;
};
