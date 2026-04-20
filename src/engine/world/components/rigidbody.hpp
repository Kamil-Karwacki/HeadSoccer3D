#pragma once
#include <glm/glm.hpp>

#include "world/component.hpp"

struct Rigidbody : public Component
{
    Rigidbody(float mass, float restitution, float friction,
              float linearDamping, float angularDamping)
        : m_inverseMass(1.0f / mass), m_linearDamping(linearDamping),
          m_angularDamping(angularDamping)
    {
    }

    virtual ~Rigidbody() override = default;

    float m_inverseMass = 1.0f;

    float m_linearDamping = 0.9f;
    float m_angularDamping = 0.9f;

    glm::mat3 m_invInertiaTensor = glm::mat3(1.0f);
    glm::mat3 m_invInertiaTensorWorld = glm::mat3(1.0f);

    glm::vec3 m_velocity = glm::vec3(0.0f);
    glm::vec3 m_angularVelocity = glm::vec3(0.0f);

    glm::vec3 m_forceAcc = glm::vec3(0.0f);
    glm::vec3 m_torqueAcc = glm::vec3(0.0f);

    glm::vec3 m_lastFrameAcc = glm::vec3(0.0f);

    void setMass(float mass)
    {
        m_inverseMass = (mass == 0.0f) ? 0.0f : 1.0f / mass;
    }
    float getMass()
    {
        return (m_inverseMass == 0.0f) ? 0.0f : (1.0f / m_inverseMass);
    }

    static glm::mat3 createBoxInverseInertiaTensor(float mass, float dx,
                                                   float dy, float dz);
    static glm::mat3 createSphereInverseInertiaTensor(float mass, float radius);
};
