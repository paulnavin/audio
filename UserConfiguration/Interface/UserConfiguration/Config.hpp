#pragma once

#include <ErrorHandling/Result.hpp>
#include <Stl/StlWrapper.hpp>

class ConfigStore {

public:
    ConfigStore() = default;
    ~ConfigStore() = default;

public:
    const int32_t GetInt32(const std::string& key, const int32_t& defaultValue) const;

public:
    Result LoadConfig(const std::string& fileName);

    using KeyValueMap = std::map<std::string, std::string>;
    using KvmSet = std::map<std::string, KeyValueMap>;
    KeyValueMap allValues_;
};
