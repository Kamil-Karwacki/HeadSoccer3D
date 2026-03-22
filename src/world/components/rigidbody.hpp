#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"
#include "world/components/collider.hpp"

class Rigidbody : public Component
{
public:
    float m_restitution;
    float m_friction;

    void start() override;
};