#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"
#include "world/components/collider.hpp"

class Rigidbody : public Component
{
public:
    float m_restitution;
    float m_friction;

    float m_linearDamping = 0.99f;
    float m_angularDamping = 0.99f;
    
    void start() override;
    void update(float deltaTime) override;

    void setMass(float mass) { m_inverseMass = (mass == 0.0f) ? 0.0f : 1.0f / mass; }
    void setInverseMass(float mass) { m_inverseMass = mass; }
    float getMass() { return (m_inverseMass == 0.0f) ? 0.0f : (1.0f / m_inverseMass); }
    float getInverseMass() { return m_inverseMass; }

    void addForce(glm::vec3 force) { m_forceAccumulated += force; }
    void addTorque(glm::vec3 torque) { m_torqueAccumulated += torque; }

    glm::vec3 getVelocity() { return m_velocity; }
    void setVelocty(glm::vec3 velocity) { m_velocity = velocity; }

    glm::vec3 getAngulatVelocity() { return m_angularVelocity; }
    void setAngularVelocity(glm::vec3 velocity) { m_angularVelocity = velocity; }
    
    void setInertiaTensor(const glm::mat3& matrix) { m_inverseInertiaTensor = glm::inverse(matrix); }
    glm::mat3 getLocalInertiaTensor() { return m_inverseInertiaTensor; }
    glm::mat3 getWorldInertiaTensor() { return m_inverseInertiaTensorWorld; }

private:
    float m_inverseMass = 1.0f;
    glm::mat3 m_inverseInertiaTensor = glm::mat3(1.0f);
    glm::mat3 m_inverseInertiaTensorWorld = glm::mat3(1.0f);

    glm::vec3 m_velocity = glm::vec3(0);
    glm::vec3 m_angularVelocity = glm::vec3(0);

    glm::vec3 m_forceAccumulated = glm::vec3(0);
    glm::vec3 m_torqueAccumulated = glm::vec3(0);
};