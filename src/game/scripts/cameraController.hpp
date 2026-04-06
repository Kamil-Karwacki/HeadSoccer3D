#pragma once
#include "world/behaviour.hpp"
#include <glm/glm.hpp>

class CameraController : public Behaviour
{
public:
    CameraController(Entity* playerEntity) : m_playerEntity(playerEntity) {}

    Entity* m_playerEntity = nullptr;

    void onUpdate(float deltaTime) override;

    float m_distToPlayer = 10.0f;
    glm::vec3 m_offset = glm::vec3(0.0f, 5.0f, 0.0f);
};