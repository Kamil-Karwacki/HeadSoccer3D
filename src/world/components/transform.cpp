#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Transform::setPosition(const glm::vec3& position)
{
    m_position = position;
    m_isDirty = true;
}

void Transform::setRotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
    m_isDirty = true;
}

void Transform::setScale(const glm::vec3& scale)
{
    m_scale = scale;
    m_isDirty = true;
}

const glm::mat4& Transform::getModelMatrix()
{
    if (m_isDirty)
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);
        
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
        m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
        
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        m_isDirty = false;
    }

    return m_modelMatrix;
}