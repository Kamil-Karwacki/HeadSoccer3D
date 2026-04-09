#pragma once
#include <vector>

#include "world/entity.hpp"

class RenderSystem
{
   public:
    RenderSystem(unsigned int whiteTextureId) : m_whiteTextureId(whiteTextureId)
    {
    }

    void render(std::vector<std::unique_ptr<Entity>>& entities, Entity* cameraEntity);

    unsigned int m_whiteTextureId;
};
