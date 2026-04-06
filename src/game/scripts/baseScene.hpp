#pragma once
#include "world/scene.hpp"

class BaseScene : public Scene
{
public:    
    using Scene::Scene;
    void init() override;
    void update(float deltaTime) override;
    void fixedUpdate(float deltaTime) override;
    void draw() override;

private:
};
