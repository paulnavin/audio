#include <Platform/Icon.hpp>

const HICON Icon::GetHandle() const {
    return handle_;
}

Result Icon::Init(const HINSTANCE& appInstance, const LPCSTR& iconName) {
    Result initResult{};
    handle_ = LoadIcon(appInstance, iconName);
    if (handle_ == NULL) {
        initResult.AppendError("Error loading icon.");
    }

    return initResult;
}
