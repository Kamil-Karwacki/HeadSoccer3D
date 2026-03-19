#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PlayerController : public Component
{
private:
    glm::vec3 m_front;
public:
    PlayerController() = default;
    ~PlayerController() = default;
    void start() override;
    void update(float deltaTime) override;
    glm::mat4 GetViewMatrix();
};