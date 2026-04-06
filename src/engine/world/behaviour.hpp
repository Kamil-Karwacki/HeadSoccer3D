#pragma once
#include "component.hpp"


class Behaviour : public Component
{
public:
    virtual void onStart() {}
    virtual void onUpdate(float deltaTime) {}
};
