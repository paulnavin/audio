#include <Platform/Cursor.hpp>

const HCURSOR Cursor::GetHandle() const {
    return handle_;
}

Result Cursor::Init(const HINSTANCE& appInstance, const LPCSTR& cursorName) {
    Result initResult{};
    handle_ = LoadCursor(appInstance, cursorName);
    if (handle_ == NULL) {
        initResult.AppendError("Error loading cursor.");
    }

    return initResult;
}
