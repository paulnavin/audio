#pragma once

#include <FileSystem/File.hpp>

Result File::Init(const std::string& fileName) {
    Result initResult{};
    
    std::ifstream file(fileName);
    if (file.is_open() == false) {
        initResult.AppendError("File::Init() : Couldn't open file.");
        initResult.AppendError(fileName.c_str());
        return initResult;
    }

    std::string line;
    while (getline(file, line)) {
        lines_.push_back(line);
    }

    if (file.bad()) {
        initResult.AppendError("File::Init() : Couldn't read file.");
        return initResult;
    }
    file.close();
    return initResult;
}

const std::string& File::GetLine(const size_t& index) const {
    return lines_.at(index);
}
