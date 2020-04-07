#pragma once

#include <ErrorHandling/Result.hpp>
class ResourceManager {
public:
    static void ShowOpenFileDialog();

private:
    ResourceManager() = delete;
    ~ResourceManager() = delete;
};
