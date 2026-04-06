#pragma once
#include "world/behaviour.hpp"
#include <glm/glm.hpp>

class Footballer : public Behaviour
{
public:
    void onUpdate(float deltaTime) override;

    void kickBall();
    void move();

    float m_kickStrength = 10.0f;
    glm::vec2 m_input = glm::vec2(0.0f);
    float m_angularInput = 0.0f;
};