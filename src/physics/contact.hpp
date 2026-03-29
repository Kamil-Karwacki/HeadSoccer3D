#pragma once
#include <glm/glm.hpp>
#include "world/components/rigidbody.hpp"

class Contact
{
public:
    Contact()
    {
        m_body[0] = nullptr;
        m_body[1] = nullptr;
        m_friction = 0.0f;
        m_restitution = 0.2f;
        m_penetration = 0.0f;
    }
    Rigidbody* m_body[2];

    glm::vec3 m_relativeContactPosition[2];
    glm::vec3 m_contactPoint;
    glm::vec3 m_contactNormal;
    
    float m_penetration;
    float m_restitution;
    float m_friction;
    
    glm::vec3 m_contactVelocity;
    float m_desiredDeltaVelocity;
    glm::mat3 m_contactToWorld;
    void calculateContactBasis();
    void calculateInternals(float deltaTime);
    void calculateDesiredDeltaVelocity(float deltaTime);
    void applyPositionChange(glm::vec3 linearChange[2], glm::vec3 angularChange[2], float penetration);
    void applyVelocityChange(glm::vec3 velocityChange[2], glm::vec3 rotationChange[2]);
    glm::vec3 calculateFrictionlessImpulse();
    glm::vec3 calculateFrictionImpulse();
    glm::vec3 calculateLocalVelocity(unsigned int bodyIndex, float deltaTime);
};