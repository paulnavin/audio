#pragma once

#include <ErrorHandling/Result.hpp>

class ResourceLocator {
public:
    ResourceLocator() = default;
    ~ResourceLocator() = default;

public:
    const std::string GetAnimatedSpriteDirectoryName() const;
    const std::string GetFullAnimatedSpriteFileName(const std::string& fileName) const;
    const std::string GetCursorDirectoryName() const;
    const std::string GetFullCursorFileName(const std::string& fileName) const;
    const std::string GetImageDirectoryName() const;
    const std::string GetFullImageFileName(const std::string& fileName) const;
    const std::string GetLogDirectoryName() const;
    const std::string GetLogFileName() const;
    const std::string GetShaderDirectoryName() const;
    const std::string GetUserConfigDirectoryName() const;

private:
};

