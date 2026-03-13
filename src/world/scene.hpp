#pragma once
#include <vector>
#include "entity.hpp"


class Scene
{
public:    
    Scene() = default;
    ~Scene() = default;
    virtual void init();
    void update(float deltaTime);
    void draw();

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
};