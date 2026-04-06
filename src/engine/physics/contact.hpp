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
    /// @brief Desired velocity change after collision.
    float m_desiredDeltaVelocity;
    /// @brief Matrix that transform world space to contact space.
    glm::mat3 m_contactToWorld;

    /// @brief Generates contact matrix that allows to go from world space to contact space.
    /// The matrix consists of three vectors: contact normal, and two contact tangents.
    void calculateContactBasis();

    /// @brief Calculates contact to world matrix, relative contact position, contact velocity
    /// and desired delta velocity;
    /// @param deltaTime Time between simulation steps in seconds.
    void calculateInternals(float deltaTime);

    /// @brief Calculates desired velocity change after collision.
    /// @param deltaTime Time between simulation steps in seconds.
    void calculateDesiredDeltaVelocity(float deltaTime);

    /// @brief Moves objects' apart after collision.
    /// @param linearChange How much objects' position changed.
    /// @param angularChange How much objects' rotation changed.
    /// @param penetration How much objects' position and rotation will change.
    void applyPositionChange(glm::vec3 linearChange[2], glm::vec3 angularChange[2], float penetration);

    /// @brief Changes objects' velocity after collision.
    /// @param velocityChange how much objects' linear velocity will change.
    /// @param rotationChange how much objects' angular velocity will change. 
    void applyVelocityChange(glm::vec3 velocityChange[2], glm::vec3 rotationChange[2]);

    /// @brief Calculates impulse that will set two objects apart. Friction is ignored.
    /// @return Impulse that separates both objects apart. 
    glm::vec3 calculateFrictionlessImpulse();

    /// @brief Calculates impulse that will set two objects apart. Friction is included. 
    /// @return Impulse that seperates both objects apart.
    glm::vec3 calculateFrictionImpulse();

    /// @brief Calculates local velocity of a contact point.
    /// @param bodyIndex Index of the rigidbody whose velocity will be included in calculations.
    /// @param deltaTime Time between simulation steps in seconds. 
    /// @return Local velocity. 
    glm::vec3 calculateLocalVelocity(unsigned int bodyIndex, float deltaTime);
};