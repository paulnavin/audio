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

private:
    std::vector<std::string> lines_;
};

