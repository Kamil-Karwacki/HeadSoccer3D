#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Transform::setPosition(const glm::vec3& position)
{
    m_position = position;
    m_isDirty = true;
}


void Transform::setRotation(const glm::quat rotation)
{
    m_rotation = rotation;
    m_isDirty = true;
}

void Transform::setRotation(const glm::vec3& eulerAngles)
{
    m_rotation = glm::quat(eulerAngles);
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
        
        m_modelMatrix *= glm::mat4_cast(m_rotation);
        
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        m_isDirty = false;
    }

    return m_modelMatrix;
}

void Transform::addRotation(const glm::quat& rotation)
{
    m_rotation = rotation * m_rotation; 
    
    m_rotation = glm::normalize(m_rotation); 
    m_isDirty = true;
}

void Transform::addRotation(const glm::vec3& eulerAngles)
{
    glm::quat deltaRotation(eulerAngles);
    addRotation(deltaRotation);
}

void Transform::addPosition(const glm::vec3& position)
{
    m_position += position;
    m_isDirty = true;
}