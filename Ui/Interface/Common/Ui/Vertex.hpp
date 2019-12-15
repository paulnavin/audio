#pragma once

static constexpr size_t POSITION_OFFSET = 0;
static constexpr size_t COLOUR_OFFSET = 3 * 4;   // 3 x sizeof(float), to offset to after positions.

struct Vertex {
    float x{};
    float y{};
    float z{};

    float red{};
    float green{};
    float blue{};
    float alpha{};
};
