#include "collider.hpp"

void Collider::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (!transform)
        std::cerr << "Warning: Collider requires transform component!\n";
}

void Collider::calculateInternals()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    if(transform)
    {
        m_cachedWorldTransform = transform->getModelMatrix() * m_offset;
    }
}

const glm::mat4& Collider::getWorldTransform() const
{
    return m_cachedWorldTransform;
}

glm::vec3 Collider::getAxis(int index) const
{
    return glm::vec3(m_cachedWorldTransform[index]);
}