#include <Ui/Config.hpp>

#pragma warning(push)
#pragma warning( disable : 4514)    //  Inline function removed.
#pragma warning( disable : 4625)    //  Warning about Window having an implicitly deleted copy constructor.
#pragma warning( disable : 5026)    //  Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 5027)    //  Warning about Window having an implicitly deleted move constructor.
#pragma warning( disable : 4626)    //  Warning about Window having an implicitly deleted assignment operator.
#pragma warning( disable : 4571)    //  Something about catch(...) semantics.
#pragma warning( disable : 5039)	//  disable pointer or reference to potentially throwing function passed to extern C function warning
#pragma warning( disable : 4820)    //  Struct padding warning
#pragma warning( disable : 4365)    //  Conversion from long to stuff warning
#pragma warning( disable : 4774)    //  'sprintf_s' : format string expected in argument 3 is not a string literal
#pragma warning( disable : 4710)    //  function not inlined
#pragma warning( disable : 4577)    //  noexcept
#pragma warning( disable : 4530)    //  C++ exception handler used, but unwind semantics are not enabled
#pragma warning( disable : 4061)    //  enumerator 'D3D_SRV_DIMENSION_UNKNOWN' in switch of enum 'D3D_SRV_DIMENSION' is not explicitly handled by a case label
#pragma warning( disable : 4668)    //  '_WIN32_WINNT_WIN10_RS2' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'

#pragma warning( disable : 4242)    //  Conversion from int to char (using ::tolower) in GetBoolean()
#pragma warning( disable : 4244)    //  Conversion from int to char (using ::tolower) in GetBoolean()

#include <Ui/IniReader.hpp>

#pragma warning(pop)    // Turn back on all warnings.

namespace Config {

class ConfigInternals {
public:
    using KeyValueMap = std::map<std::string, std::string>;
    using KvmSet = std::map<std::string, KeyValueMap>;

public:

    const int32_t GetInt32(const std::string& key, const int32_t& defaultValue) const {
        const KeyValueMap& kvm = allConfigs_.at(fileName_);
        
        KeyValueMap::const_iterator keyFinder = kvm.find(key);
        if (keyFinder == kvm.end()) {
            return defaultValue;
        }

        return static_cast<int32_t>(std::strtol(keyFinder->second.c_str(), nullptr, 10));
    }

    Result LoadConfig(const std::string& fileName) {
        fileName_ = fileName;
        ConfigInternals::KeyValueMap newMap;
        newMap["width"] = "1024";
        newMap["height"] = "768";
        allConfigs_[fileName] = newMap;
        return Result{};
    }

private:
    std::string fileName_;
    KvmSet allConfigs_;
};

Config::Config() {
    internals_ = new ConfigInternals();
}

Config::~Config() {
    delete internals_;
}

const int32_t Config::GetInt32(const std::string& key, const int32_t& defaultValue) const {
    return internals_->GetInt32(key, defaultValue);
}

Result Config::LoadConfig(const std::string& fileName) {
    return internals_->LoadConfig(fileName);
}

} // namespace Config
