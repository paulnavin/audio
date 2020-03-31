#pragma once

class Commander;
class GraphicsEngine;
struct ModelPortal;

struct ModelPortal {
    GraphicsEngine* gfx;
    Commander* commander;
};
