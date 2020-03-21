#pragma once

#include <ErrorHandling/Result.hpp>
#include <Stl/StlWrapper.hpp>

class File {
public:
    File() = default;
    ~File() = default;

public:
    Result Init(const std::string& fileName);

    const std::string& GetLine(const size_t& index) const;
    void PutLine(const size_t& index, const std::string& newLine);

    Result WriteToDisk();

private:
    std::vector<std::string> lines_;
    std::string fileName_;
};

