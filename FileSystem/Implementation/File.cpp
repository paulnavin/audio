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
    fileName_ = fileName;
    return initResult;
}

const std::string& File::GetLine(const size_t& index) const {
    return lines_.at(index);
}

void File::PutLine(const size_t& index, const std::string& newLine) {
    if (index < lines_.size()) {
        lines_[index] = newLine;
    } else {
        lines_.push_back(newLine);
    }
}

Result File::WriteToDisk() {
    Result writeResult{};

    std::ofstream file(fileName_);
    if (file.is_open() == false) {
        writeResult.AppendError("File::WriteToDisk() : Couldn't open file.");
        writeResult.AppendError(fileName_.c_str());
        return writeResult;
    }

    std::vector<std::string>::const_iterator lineFinder = lines_.begin();
    std::vector<std::string>::const_iterator lineEnd = lines_.end();
    while (lineFinder != lineEnd) {
        file.write(lineFinder->c_str(), static_cast<std::streamsize>(lineFinder->size()));
        file.put('\n');

        // Loop incrementer.
        ++lineFinder;
    }

    if (file.bad()) {
        writeResult.AppendError("File::WriteToDisk() : Couldn't write file.");
        return writeResult;
    }
    file.close();
    return writeResult;
}