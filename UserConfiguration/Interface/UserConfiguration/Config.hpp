#pragma once

#include <Utility/Result.hpp>
#include <Utility/StlWrapper.hpp>

namespace uc {

class ConfigInternals;

class ConfigStore {

public:
    ConfigStore();
    ~ConfigStore();

public:
    const int32_t GetInt32(const std::string& key, const int32_t& defaultValue) const;

public:
    Result LoadConfig(const std::string& fileName);

private:
    ConfigInternals* internals_;
};

} // namespace Config
