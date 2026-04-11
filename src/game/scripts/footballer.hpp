#pragma once
#include <glm/glm.hpp>

#include "scripts/ball.hpp"
#include "world/behaviour.hpp"

class Footballer : public Behaviour
{
   public:
    void onUpdate(float deltaTime) override;

    void onTriggerEnter(Collider* other) override;

    void detectBall(Collider* other);
    void kickBall();
    void move(float deltaTime);

    glm::vec2 m_input = glm::vec2(0.0f);
    glm::vec2 m_rotation = glm::vec2(0.0f);

   private:
    Ball* m_ball = nullptr;
    float m_kickStrength = 200.0f;
    float m_speed = 500.0f;
};
