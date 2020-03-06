#pragma once

#include <Graphics/GraphicsEngine.hpp>
#include <Graphics/Rectangle2d.hpp>
#include <Graphics/Text2d.hpp>
#include <Graphics/Vertex.hpp>
#include <UserConfiguration/Config.hpp>
#include <UserInput/InputManager.hpp>
#include <UserInterface/WindowMessageHandler.hpp>
#include <ErrorHandling/Result.hpp>
#include <Platform/WindowsInterface.hpp>

#include "Scene1UserInput.hpp"

class Model2d;
class Model3d;
class ResourceManager;
class Window;

class Scene1Dj {
public:
    Scene1Dj() = default;
    ~Scene1Dj() = default;

public:
    Result Init(GraphicsEngine* gfx, ::uc::ConfigStore* config, InputManager* inputManager);
    void ShutDown();

public:
    // User Input Commands
    void OnCommandMouseClicked(const float& x, const float& y);
    void OnCommandRecreateModels();
    void OnCommandShowFps();
    void OnCommandShowMousePosition();

    void UpdateMousePosition(const float& x, const float& y);

public:
    void Update(const double& dt);
    Result UpdateFps(const int64_t& newFps);

private:
    // Modelling
    void Destroy3dModel();
    void Destroy2dModel();
    Result Create3dModel();
    Result Create2dModel();

private:
    GraphicsEngine* graphicsEngine_;
    Model3d* model3d_;
    Model2d* djModel2d_;
    bool showFps_ = true;
    bool showMousePosition_ = true;
    Window* mainWindow_;
    Scene1UserInput userInputHandler_;
};
