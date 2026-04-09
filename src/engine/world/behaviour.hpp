#pragma once
#include "component.hpp"
#include "world/components/collider.hpp"

class Behaviour : public Component
{
   public:
    virtual void onStart()
    {
    }
    virtual void onUpdate(float deltaTime)
    {
    }
    virtual void onTriggerEnter(Collider* otherCollider)
    {
    }
    virtual void onCollisionEnter(Collider* otherCollider)
    {
    }
};
