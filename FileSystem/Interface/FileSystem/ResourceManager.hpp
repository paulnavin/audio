#pragma once

#include <ErrorHandling/Result.hpp>

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    const std::string GetAnimatedSpriteDirectoryName() const;
    const std::string GetFullAnimatedSpriteFileName(const std::string& fileName) const;
    const std::string GetCursorDirectoryName() const;
    const std::string GetFullCursorFileName(const std::string& fileName) const;
    const std::string GetLogDirectoryName() const;
    const std::string GetLogFileName() const;
    const std::string GetShaderDirectoryName() const;

private:
};
