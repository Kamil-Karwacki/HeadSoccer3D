#pragma once
#include <glm/glm.hpp>
#include "world/components/rigidbody.hpp"

class Contact
{
public:
    Rigidbody* m_body[2];

    glm::vec3 m_contactPoint;
    glm::vec3 m_contactNormal;
    
    float m_penetration;
    float m_restitution;
    float m_friction;
};