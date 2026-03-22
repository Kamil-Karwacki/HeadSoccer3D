#include "rigidbody.hpp"
#include <iostream>

void Rigidbody::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    Collider* collider = m_entity->GetComponent<Collider>();
    
    if (!transform)
        std::cerr << "Error: Rigidbody requires transform component!\n";

    if (!collider)
        std::cerr << "Error: Rigidbody requires collider component!\n";
}

void Rigidbody::update(float deltaTime)
{
    glm::vec3 acceleration = m_forceAccumulated * m_inverseMass;
    m_velocity += acceleration * deltaTime;

    glm::vec3 angularAcceleration = m_torqueAccumulated * m_inverseInertiaTensor;
    m_angularVelocity += angularAcceleration * deltaTime;

    m_velocity *= pow(m_linearDamping, deltaTime);
    m_angularVelocity *= pow(m_angularDamping, deltaTime);

    Transform* transform = m_entity->GetComponent<Transform>();
    glm::vec3 oldPosition = transform->getPosition();
    transform->setPosition(oldPosition + m_velocity * deltaTime);

    glm::vec3 oldRotation = transform->getRotation();
    transform->setRotation(oldRotation + m_angularVelocity * deltaTime);

    // Update inverse inertia tensor world due to objects rotation.
    glm::mat4 modelMatrix = transform->getModelMatrix();
    glm::mat3 rotationMatrix = glm::mat3(modelMatrix);
    m_inverseInertiaTensorWorld = rotationMatrix * m_inverseInertiaTensor * glm::transpose(rotationMatrix);

    m_forceAccumulated = glm::vec3(0.0f);
    m_torqueAccumulated = glm::vec3(0.0f);
}