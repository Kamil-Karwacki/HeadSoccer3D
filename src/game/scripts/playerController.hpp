#pragma once
#include <glm/glm.hpp>
#include "world/behaviour.hpp"

class PlayerController : public Behaviour
{
public:
    void onStart() override;
    void onUpdate(float deltaTime) override;
    virtual ~PlayerController() override = default;

private:
    float m_yaw = 0.0f;
};