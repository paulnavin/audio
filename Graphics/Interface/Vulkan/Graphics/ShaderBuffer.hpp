#pragma once

struct ShaderBuffer {
    ShaderBuffer() = default;
    ~ShaderBuffer() = default;

    byte* buffer = nullptr;
    size_t size{};
};
