#pragma once

#include <Utility/Result.hpp>

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    const std::string GetLogDirectoryName() const;
    const std::string GetLogFileName() const;
    const std::string GetShaderDirectoryName() const;

private:
};

