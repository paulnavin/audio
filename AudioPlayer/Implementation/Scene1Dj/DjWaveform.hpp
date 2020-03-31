#pragma once

#include <UserInterface/Element.hpp>
#include <UserInterface/Rectangle2d.hpp>

struct ModelPortal;

class DjWaveform : public Element {
public:
    DjWaveform() = default;
    virtual ~DjWaveform() = default;

public:
    virtual Result Init(ModelPortal* portal) override;

private:
    Rectangle2d window_;
};

