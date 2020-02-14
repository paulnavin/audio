#pragma once

#include <Utility/ResourceManager.hpp>

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
