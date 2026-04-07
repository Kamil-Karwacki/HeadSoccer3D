#pragma once
#include "component.hpp"


class Behaviour : public Component
{
public:
    virtual void onStart() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onTriggerEnter(Entity* other) {}
    virtual void onCollisionEnter(Entity* other) {}
};
