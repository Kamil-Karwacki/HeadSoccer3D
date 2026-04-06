#include "rigidbody.hpp"
#include <iostream>
/*
void Rigidbody::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    Collider* collider = m_entity->GetComponent<Collider>();
    
    if (!transform)
        std::cerr << "Error: Rigidbody requires transform component!\n";

    if (!collider)
        std::cerr << "Error: Rigidbody requires collider component!\n";
}
*/
void Rigidbody::integrate(float deltaTime)
{
    glm::vec3 acceleration = m_forceAccumulated * m_inverseMass;
    m_velocity += acceleration * deltaTime;
    
    glm::vec3 angularAcceleration = m_inverseInertiaTensorWorld * m_torqueAccumulated;
    m_angularVelocity += angularAcceleration * deltaTime;

    m_velocity *= pow(m_linearDamping, deltaTime);
    m_angularVelocity *= pow(m_angularDamping, deltaTime);

    m_lastFrameAcc = acceleration;

    Transform* transform = m_entity->GetComponent<Transform>();
    transform->addPosition(m_velocity * deltaTime);
    transform->addRotation(m_angularVelocity * deltaTime);

    // Update inverse inertia tensor world due to objects rotation.
    glm::mat4 modelMatrix = transform->getModelMatrix();
    glm::mat3 rotationMatrix = glm::mat3(modelMatrix);
    m_inverseInertiaTensorWorld = rotationMatrix * m_inverseInertiaTensor * glm::transpose(rotationMatrix);

    m_forceAccumulated = glm::vec3(0.0f);
    m_torqueAccumulated = glm::vec3(0.0f);
}

glm::mat3 Rigidbody::createBoxInverseInertiaTensor(float mass, float dx, float dy, float dz) {
    if (mass <= 0.0f) return glm::mat3(0.0f);

    float ix = (1.0f / 12.0f) * mass * (dy * dy + dz * dz);
    float iy = (1.0f / 12.0f) * mass * (dx * dx + dz * dz);
    float iz = (1.0f / 12.0f) * mass * (dx * dx + dy * dy);

    glm::mat3 invInertia(0.0f);
    invInertia[0][0] = 1.0f / ix;
    invInertia[1][1] = 1.0f / iy;
    invInertia[2][2] = 1.0f / iz;

    return invInertia;
}


glm::mat3 Rigidbody::createSphereInverseInertiaTensor(float mass, float radius) {
    if (mass <= 0.0f) return glm::mat3(0.0f);

    float invI = 2.5f / (mass * radius * radius);

    glm::mat3 invInertia(0.0f);
    
    invInertia[0][0] = invI;
    invInertia[1][1] = invI;
    invInertia[2][2] = invI;

    return invInertia;
}