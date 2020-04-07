#pragma once

#include <FileSystem/ResourceLocator.hpp>

const std::string ResourceLocator::GetAnimatedSpriteDirectoryName() const {
    return "..\\..\\..\\Resources\\AnimatedSprites";
}

const std::string ResourceLocator::GetFullAnimatedSpriteFileName(const std::string& fileName) const {
    std::string fullName = GetAnimatedSpriteDirectoryName();
    fullName.append("\\");
    fullName.append(fileName);
    return fullName;
}

const std::string ResourceLocator::GetCursorDirectoryName() const {
    return "..\\..\\..\\Resources\\Cursors";
}

const std::string ResourceLocator::GetFullCursorFileName(const std::string& fileName) const {
    std::string fullName = GetCursorDirectoryName();
    fullName.append("\\");
    fullName.append(fileName);
    return fullName;
}

const std::string ResourceLocator::GetLogDirectoryName() const {
    return ".\\Resources\\Logging";
}

const std::string ResourceLocator::GetLogFileName() const {
    std::string directory = GetLogDirectoryName();
    directory.append("\\runtime_log.txt");
    return directory;
}

const std::string ResourceLocator::GetShaderDirectoryName() const {
    return ".\\";
}

const std::string ResourceLocator::GetUserConfigDirectoryName() const {
    return ".\\Resources\\Config";
}