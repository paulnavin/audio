#include <UserInterface/Button.hpp>

#include <UserInput/UserInputCommands.hpp>
#include <UserInterface/ModelPortal.hpp>
#include <Platform/Commander.hpp>

Button::~Button() {
    chell_->commander->UnsubscribeFromMouseMove(this);
}

Result Button::Init(ModelPortal* portal) {
    Result initResult = Element::Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Button::Init() : Error initialising base Element.");
        return initResult;
    }

    chell_->commander->SubscribeToMouseMove(this);

    if (backgroundImageName_ != nullptr) {
        backgroundImage_.SetParent(this);
        backgroundImage_.SetBitmapName(backgroundImageName_);
        backgroundImage_.SetPosition(0.0f, 0.0f);
        backgroundImage_.SetDimensionsAsPercentage(100.0f, 100.0f);
        initResult = backgroundImage_.Init(portal);

        if (initResult.HasErrors()) {
            initResult.AppendError("Button::Init() : Error initialising background image.");
            return initResult;
        }
    } else {
        background_.SetParent(this);
        background_.SetColour(Colour{ 1.0f, 0.0f, 0.0f, 0.6f });
        background_.SetPosition(0.0f, 0.0f);
        background_.SetDimensionsAsPercentage(100.0f, 100.0f);
        initResult = background_.Init(portal);
        if (initResult.HasErrors()) {
            initResult.AppendError("Button::Init() : Error initialising background.");
            return initResult;
        }
    }

    if (foregroundImageName_ != nullptr) {
        foregroundImage_.SetParent(this);
        foregroundImage_.SetBitmapName(foregroundImageName_);
        foregroundImage_.SetPosition(0.0f, 0.0f);
        foregroundImage_.SetDimensionsAsPercentage(100.0f, 100.0f);
        initResult = foregroundImage_.Init(portal);

        if (initResult.HasErrors()) {
            initResult.AppendError("Button::Init() : Error initialising foreground image.");
            return initResult;
        }
    }

    mouseOverHighlight_.SetParent(this);
    mouseOverHighlight_.SetColour(Colour{ 1.0f, 1.0f, 1.0f, 0.1f });
    mouseOverHighlight_.SetPosition(0.0f, 0.0f);
    mouseOverHighlight_.SetDimensionsAsPercentage(100.0f, 100.0f);
    mouseOverHighlight_.SetEnabled(false);
    initResult = mouseOverHighlight_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Button::Init() : Error initialising mouse over highlight.");
        return initResult;
    }

    buttonDownHighlight_.SetParent(this);
    buttonDownHighlight_.SetColour(Colour{ 0.0f, 0.0f, 1.0f, 0.5f });
    buttonDownHighlight_.SetPosition(0.0f, 0.0f);
    buttonDownHighlight_.SetDimensionsAsPercentage(100.0f, 100.0f);
    buttonDownHighlight_.SetEnabled(false);
    initResult = buttonDownHighlight_.Init(portal);
    if (initResult.HasErrors()) {
        initResult.AppendError("Button::Init() : Error initialising mouse down highlight.");
        return initResult;
    }

    if (backgroundImageName_ != nullptr) {
        AddChild(&backgroundImage_);
    } else {
        AddChild(&background_);
    }

    if (foregroundImageName_ != nullptr) {
        AddChild(&foregroundImage_);
    }
    AddChild(&mouseOverHighlight_);
    AddChild(&buttonDownHighlight_);

    chell_->commander->Subscribe(LeftButtonUp, this);

    return initResult;
}

bool Button::OnClick() {
    if (background_.GetColour().red > 0.1f) {
        background_.SetColour(Colour{ 0.0f, 0.5f, 0.0f, 0.5f });
    } else {
        background_.SetColour(Colour{ 0.5f, 0.0f, 0.0f, 0.5f });
    }

    return true;
}

void Button::HandleCommand(const CommandId& command) {
    switch (command) {
        case LeftButtonDown: {
            buttonDownHighlight_.SetEnabled(true);
            buttonDownOnThisButton_ = true;
            return;
        }
        case LeftButtonUp: {
            if (buttonDownOnThisButton_ == true) {
                buttonDownHighlight_.SetEnabled(false);
                if ((mouseOver_ == true) && (onClickHandler_)) {
                    onClickHandler_();
                } else {
                    chell_->commander->Unsubscribe(LeftButtonDown, this);
                }
                buttonDownOnThisButton_ = false;
            }
            return; 
        }
    }
}

void Button::HandleMouseMove(const float& x, const float& y) {
    if (x >= positionOnScreen_.x &&
        x <= positionOnScreen_.x + dimensionsOnScreen_.width &&
        y >= positionOnScreen_.y && 
        y <= positionOnScreen_.y + dimensionsOnScreen_.height) {
        if (mouseOver_ == false) {
            mouseOver_ = true;
            mouseOverHighlight_.SetEnabled(true);
            chell_->commander->Subscribe(LeftButtonDown, this);
        }
    } else {
        if (mouseOver_ == true) {
            mouseOver_ = false;
            mouseOverHighlight_.SetEnabled(false);
            chell_->commander->Unsubscribe(LeftButtonDown, this);
        }
    }
}

void Button::SetOnClickHandler(std::function<void()> onClickHandler) {
    onClickHandler_ = onClickHandler;
}

void Button::SetBackgroundImage(const char* name) {
    backgroundImageName_ = name;
}

void Button::SetForegroundImage(const char* name) {
    foregroundImageName_ = name;
}