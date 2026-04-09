#include "collider.hpp"
glm::vec3 TransformableCollider::getAxis(int index) const
{
    return glm::vec3(m_worldTransform[index]);
}
