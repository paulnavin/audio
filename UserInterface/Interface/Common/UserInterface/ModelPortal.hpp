#pragma once

class Commander;
class GraphicsEngine;
class ResourceManager;

struct ModelPortal {
    GraphicsEngine* gfx;
    Commander* commander;
    ResourceManager* resourceManager;
};
