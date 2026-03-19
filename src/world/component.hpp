#pragma once

class Entity; 

class Component
{
public:
    virtual ~Component() = default;

    virtual void start() {}
    virtual void update(float deltaTime) {}
    virtual void draw() {}
    
    virtual void onDestroy() {}

    Entity* m_entity = nullptr;
};