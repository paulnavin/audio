#pragma once

#include <ErrorHandling/Result.hpp>

class InputManager;
class Scene;

class SceneUserInput {
public:
    SceneUserInput() = default;
    virtual ~SceneUserInput() = default;

public:
    virtual Result Init(Scene* newScene, InputManager* inputManager);
    virtual void Update(const double& dt);

protected:
    Scene* scene_;
    InputManager* inputManager_;

private:
    void HandleLeftMouseDown(const float& x, const float& y);
    void HandleLeftMouseUp(const float& x, const float& y);

    bool leftMouseDown_ = false;
    double leftMouseDownTime_ = 0;
    float leftMouseDownX_ = 0.0f;
    float leftMouseDownY_ = 0.0f;
};

