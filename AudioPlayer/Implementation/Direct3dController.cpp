#include "Direct3dController.hpp"

Result Direct3dController::Init() {
    Result initResult;

    // D3D11_CREATE_DEVICE_BGRA_SUPPORT is needed to do both 3D and 2D.
    UINT deviceCreationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &device_, &featureLevel, &deviceContext_);

    if (FAILED(hr)) {
        initResult.AppendError("Direct3dController::Init() : Couldn't create Direct3D context.");
    } else if (featureLevel < D3D_FEATURE_LEVEL_11_0) {
        initResult.AppendError("Direct3dController::Init() : DirectX 11 isn't supported.");
    }

    return initResult;
}
