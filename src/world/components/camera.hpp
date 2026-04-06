#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include <glm/glm.hpp>

class Camera : public Component
{
public:
    virtual ~Camera() override = default;
    void start() override;
    void update(float deltaTime) override;

    glm::mat4 getView() { return m_view; }
    glm::mat4 getProjection() { return m_projection; }
    glm::vec3 getFront() { return m_front; }
private:
    void updateView();

    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
    glm::vec3 m_front = glm::vec3(1.0f);
};
