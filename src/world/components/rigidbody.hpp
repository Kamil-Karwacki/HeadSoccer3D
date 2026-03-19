#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"
#include "world/components/collider.hpp"

class Rigidbody : public Component
{
private:

public:
    float restitution;
    float friction;
    Rigidbody();

    void start() override;
};