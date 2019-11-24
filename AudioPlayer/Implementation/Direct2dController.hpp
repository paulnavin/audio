#pragma once

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

// Windows and Com
#include <wrl/client.h>

// Direct3D
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

// Direct2D
#include <d2d1_2.h>
#pragma comment (lib, "d2d1.lib")

// DirectWrite
#include <dwrite_2.h>
#pragma comment (lib, "dwrite.lib")

#include <sstream>

#pragma warning(pop)    // Turn back on all warnings.

#include "Result.hpp"

class Direct2dController {
public:
    Direct2dController() = default;
    ~Direct2dController() = default;

public:
    Result Init(const HWND& newWindowHandle, const Microsoft::WRL::ComPtr<ID3D11Device>& newDevice3d, const Microsoft::WRL::ComPtr<IDXGISwapChain>& new3dSwapChain);
    Result RenderFps();
    Result SetFpsValue(const int64_t& newFps);

private:
    Result CreateDevice();
    Result CreateBitmapRenderTarget();
    Result InitialiseTextFormats();

private:

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> fpsBrush_;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> fpsTextFormat_;
    Microsoft::WRL::ComPtr<IDWriteTextLayout> fpsTextLayout_;

    Microsoft::WRL::ComPtr<ID3D11Device> device3d_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain3d_;

    Microsoft::WRL::ComPtr<ID2D1Device1> device2d_;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1> deviceContext2d_;
    Microsoft::WRL::ComPtr<ID2D1Factory2> factory2d_;
    Microsoft::WRL::ComPtr<IDWriteFactory2> writeFactory_;
    HWND windowHandle_;
};
