#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PlayerController : public Component
{
public:
    PlayerController() = default;
    ~PlayerController() = default;
    void start() override;
    void update(float deltaTime) override;
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
private:
    float m_yaw = 0.0f;
    float m_pitch = 0.0f;

    glm::vec3 m_front;
    glm::mat4 m_projection;
};