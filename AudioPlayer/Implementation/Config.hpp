#pragma once

#include "Result.hpp"
#include "StlWrapper.hpp"

namespace Config {

class ConfigInternals;

class Config {

public:
    Config();
    ~Config();

public:
    const int32_t GetInt32(const std::string& key, const int32_t& defaultValue) const;

public:
    Result LoadConfig(const std::string& fileName);

private:
    ConfigInternals* internals_;
};

} // namespace Config
