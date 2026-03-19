#pragma once
#include "world/component.hpp"
#include <glm/glm.hpp>
#include <iostream>

class Transform : public Component 
{
public:
    Transform() = default;

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scale);
    const glm::mat4& getModelMatrix();
private:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    bool m_isDirty = true;
};