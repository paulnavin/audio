#include <UserConfiguration/Config.hpp>

#include <FileSystem/File.hpp>


const int32_t ConfigStore::GetInt32(const std::string& key, const int32_t& defaultValue) const {
    KeyValueMap::const_iterator keyFinder = allValues_.find(key);
    if (keyFinder == allValues_.end()) {
        return defaultValue;
    }

    return static_cast<int32_t>(std::strtol(keyFinder->second.c_str(), nullptr, 10));
}

Result ConfigStore::LoadConfig(const std::string& fileName) {
    File configFile;

    // Some default shit.
    allValues_.clear();
    allValues_["width"] = "1600";
    allValues_["height"] = "900";

    Result loadResult = configFile.Init(fileName);
    if (loadResult.HasErrors() == false) {
        for (size_t i = 0; i < 2; ++i) {
            std::string line = configFile.GetLine(i);
            std::istringstream stringStream(line);

            std::string key;
            std::string delimeter;
            std::string value;

            stringStream >> key;
            stringStream >> delimeter;
            stringStream >> value;

            allValues_[key] = value;
        }
    }

    configFile.PutLine(1, "height = 768");
    configFile.PutLine(0, "width = 1024");
    Result writeResult = configFile.WriteToDisk();
    if (writeResult.HasErrors()) {
        writeResult.AppendError("Config::Init() : Error writing back out to disk.");
        // TODO: Think about how to deal with warnings.
        //return writeResult;
    }

    // Always return a good result - if the file wasn't loaded, use defaults.
    return Result{};
}
