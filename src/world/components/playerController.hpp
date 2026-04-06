#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PlayerController : public Component
{
public:
    virtual ~PlayerController() override = default;

    void start() override;
    void update(float deltaTime) override;
private:
    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 1.0f);
};