#pragma once

#include <FileSystem/ResourceManager.hpp>

const std::string ResourceManager::GetAnimatedSpriteDirectoryName() const {
    return "..\\..\\..\\Resources\\AnimatedSprites";
}

const std::string ResourceManager::GetFullAnimatedSpriteFileName(const std::string& fileName) const {
    std::string fullName = GetAnimatedSpriteDirectoryName();
    fullName.append("\\");
    fullName.append(fileName);
    return fullName;
}

const std::string ResourceManager::GetCursorDirectoryName() const {
    return "..\\..\\..\\Resources\\Cursors";
}

const std::string ResourceManager::GetFullCursorFileName(const std::string& fileName) const {
    std::string fullName = GetCursorDirectoryName();
    fullName.append("\\");
    fullName.append(fileName);
    return fullName;
}

const std::string ResourceManager::GetLogDirectoryName() const {
    return ".\\Resources\\Logging";
}

const std::string ResourceManager::GetLogFileName() const {
    std::string directory = GetLogDirectoryName();
    directory.append("\\runtime_log.txt");
    return directory;
}

const std::string ResourceManager::GetShaderDirectoryName() const {
    return ".\\";
}
