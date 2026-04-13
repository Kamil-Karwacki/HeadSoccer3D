#pragma once
#include "world/component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

class Transform : public Component
{
  public:
    Transform() = default;
    Transform(glm::vec3 position) : m_position(position) {}
    Transform(glm::vec3 position, glm::vec3 rotation) : m_position(position)
    {
        setRotation(rotation);
    }
    virtual ~Transform() override = default;

    glm::vec3 getPosition() const { return m_position; }
    glm::quat getRotation() const { return m_rotation; }
    glm::vec3 getEulerAngles() const { return glm::eulerAngles(m_rotation); }
    glm::vec3 getScale() const { return m_scale; }

    void setPosition(const glm::vec3 &position);
    void addPosition(const glm::vec3 &position);
    void setRotation(const glm::quat rotation);
    void setRotation(const glm::vec3 &eulerAngles);
    void addRotation(const glm::quat &rotation);
    void addRotation(const glm::vec3 &eulerAngles);
    void setScale(const glm::vec3 &scale);

    glm::vec3 getFront() const
    {
        return glm::normalize(m_rotation * glm::vec3(0.0f, 0.0f, -1.0f));
    }
    void lookAt(const glm::vec3 &targetPoint);

    const glm::mat4 &getModelMatrix();

  private:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    bool m_isDirty = true;
};
