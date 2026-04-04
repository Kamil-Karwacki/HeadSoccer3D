#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"
#include "world/components/collider.hpp"

class Rigidbody : public Component
{
public:
    Rigidbody(float mass, float restitution, float friction, float linearDamping, float angularDamping) : 
        m_restitution(restitution), m_friction(friction), m_inverseMass(1.0f / mass), 
        m_linearDamping(linearDamping), m_angularDamping(angularDamping) {}
        
    float m_restitution;
    float m_friction;

    float m_linearDamping = 0.9f;
    float m_angularDamping = 0.9f;
    
    void start() override;
    void integrate(float deltaTime);

    void setMass(float mass) { m_inverseMass = (mass == 0.0f) ? 0.0f : 1.0f / mass; }
    void setInverseMass(float mass) { m_inverseMass = mass; }
    float getMass() { return (m_inverseMass == 0.0f) ? 0.0f : (1.0f / m_inverseMass); }
    float getInverseMass() { return m_inverseMass; }

    void addForce(glm::vec3 force) { m_forceAccumulated += force; }
    void addTorque(glm::vec3 torque) { m_torqueAccumulated += torque; }

    void addVelocity(glm::vec3 velocity) { m_velocity += velocity; }
    void addAngularVelocity(glm::vec3 velocity) { m_angularVelocity += velocity; }

    glm::vec3 getVelocity() { return m_velocity; }
    void setVelocty(glm::vec3 velocity) { m_velocity = velocity; }

    glm::vec3 getAngularVelocity() { return m_angularVelocity; }
    void setAngularVelocity(glm::vec3 velocity) { m_angularVelocity = velocity; }
    
    void setInertiaTensor(const glm::mat3& matrix) { m_inverseInertiaTensor = glm::inverse(matrix); }
    void setInverseInertiaTensor(const glm::mat3& matrix) { m_inverseInertiaTensor = matrix; }

    static glm::mat3 createBoxInverseInertiaTensor(float mass, float dx, float dy, float dz);
    static glm::mat3 createSphereInverseInertiaTensor(float mass, float radius);

    glm::mat3 getLocalInertiaTensor() { return m_inverseInertiaTensor; }
    glm::mat3 getWorldInertiaTensor() { return m_inverseInertiaTensorWorld; }
    
    glm::vec3 getLastFrameAcceleration() { return m_lastFrameAcc; }
private:
    float m_inverseMass;
    glm::mat3 m_inverseInertiaTensor = glm::mat3(1.0f);
    glm::mat3 m_inverseInertiaTensorWorld = glm::mat3(1.0f);

    glm::vec3 m_velocity = glm::vec3(0);
    glm::vec3 m_angularVelocity = glm::vec3(0);

    glm::vec3 m_forceAccumulated = glm::vec3(0);
    glm::vec3 m_torqueAccumulated = glm::vec3(0);
    
    glm::vec3 m_lastFrameAcc;
};