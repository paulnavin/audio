#pragma once

#include <Graphics/DirectXInterface.hpp>

#include <ErrorHandling/Result.hpp>

class Engine2d;
class Window;

class TextManager2d {

public:
    TextManager2d() = default;
    ~TextManager2d() = default;

public:
    const Microsoft::WRL::ComPtr<IDWriteFactory2>& GetWriteFactory() const;

public:
    Result Init(const Window& newWindow, const Engine2d& newEngine);
    Result InitialiseFactory();

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext1>  deviceContext2d_;
    Microsoft::WRL::ComPtr<IDWriteFactory2>      writeFactory_;
};
