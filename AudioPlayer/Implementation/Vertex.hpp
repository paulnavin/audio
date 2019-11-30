#pragma once

static constexpr size_t POSITION_OFFSET = 0;
static constexpr size_t COLOUR_OFFSET = 3 * 12;   // 3 x sizeof(float)

struct Vertex {
    Vertex() = default;
    ~Vertex() = default;

    float x{};
    float y{};
    float z{};

    float red{};
    float green{};
    float blue{};
};
