#include "contact.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

void Contact::calculateContactBasis()
{
    glm::vec3 contactTanget[2];

    // Check which axis normal vector is farthest from, then use that axis in cross product
    if (fabsf(m_contactNormal.x) > fabsf(m_contactNormal.y))
    {
        // Calculate inverse of length so result can be normalized.
        const float s = 1.0f / sqrt(m_contactNormal.z * m_contactNormal.z + 
            m_contactNormal.x * m_contactNormal.x);

        contactTanget[0].x = m_contactNormal.z * s;
        contactTanget[0].y = 0;
        contactTanget[0].z = -m_contactNormal.x * s;

        contactTanget[1].x = m_contactNormal.y * contactTanget[0].x;
        contactTanget[1].y = m_contactNormal.z * contactTanget[0].x - 
            m_contactNormal.x * contactTanget[0].z;
        contactTanget[1].z = -m_contactNormal.y * contactTanget[0].x;
    }
    else
    {
        // Calculate inverse of length so result can be normalized.
        const float s = 1.0f / sqrt(m_contactNormal.z * m_contactNormal.z + 
            m_contactNormal.y * m_contactNormal.y);

        contactTanget[0].x = 0;
        contactTanget[0].y = -m_contactNormal.z * s;
        contactTanget[0].z = m_contactNormal.y * s;

        contactTanget[1].x = m_contactNormal.y * contactTanget[0].z - 
            m_contactNormal.z * contactTanget[0].y;
        contactTanget[1].y = -m_contactNormal.x * contactTanget[0].z;
        contactTanget[1].z = m_contactNormal.x * contactTanget[0].y;
    }
    m_contactToWorld = glm::mat3(m_contactNormal, contactTanget[0], contactTanget[1]);
}

void Contact::calculateInternals(float deltaTime)
{
    calculateContactBasis();
    m_relativeContactPosition[0] = m_contactPoint - m_body[0]->m_entity->GetComponent<Transform>()->getPosition();
    
    if (m_body[1])
        m_relativeContactPosition[1] = m_contactPoint - m_body[1]->m_entity->GetComponent<Transform>()->getPosition();
        
    m_contactVelocity = calculateLocalVelocity(0, deltaTime);
    if (m_body[1])
        m_contactVelocity -= calculateLocalVelocity(1, deltaTime); 

    calculateDesiredDeltaVelocity(deltaTime);
}

void Contact::calculateDesiredDeltaVelocity(float deltaTime)
{
    static constexpr float velocityLimit = 0.25f;    

    float velocityFromAcc = glm::dot(m_body[0]->m_lastFrameAcc, m_contactNormal) * deltaTime;

    if(m_body[1])
        velocityFromAcc -= glm::dot(m_body[1]->m_lastFrameAcc, m_contactNormal) * deltaTime;

    float thisRestitution = m_restitution;

    // Limit the restitution so that the objects dont jump infinitely.
    if (fabsf(m_contactVelocity.x) < velocityLimit)
        thisRestitution = 0.0f;

   m_desiredDeltaVelocity = -m_contactVelocity.x - thisRestitution * (m_contactVelocity.x - velocityFromAcc);
}

glm::vec3 Contact::calculateLocalVelocity(unsigned int bodyIndex, float deltaTime)
{
    Rigidbody* body = m_body[bodyIndex];

    glm::vec3 velocity = glm::cross(body->m_angularVelocity, m_relativeContactPosition[bodyIndex]);
    velocity += body->m_velocity;

    glm::vec3 contactVelocity = glm::transpose(m_contactToWorld) * velocity;

    glm::vec3 accVelocity = body->m_lastFrameAcc * deltaTime;
    accVelocity = m_contactToWorld * accVelocity;
    accVelocity.x = 0;
    contactVelocity += accVelocity;

    return contactVelocity;
}


void Contact::applyPositionChange(glm::vec3 linearChange[2], glm::vec3 angularChange[2], float penetration)
{
    static constexpr float angularLimit = 0.2f;
    float angularMove[2];
    float linearMove[2];

    float totalInertia = 0;
    float linearInertia[2];
    float angularInertia[2];

    for (size_t i = 0; i < 2; i++)
    {
        if (!m_body[i])
            continue;

        glm::mat3 inverseInertiaTensor = m_body[i]->m_invInertiaTensorWorld;
        glm::vec3 angularInertiaWorld = glm::cross(m_relativeContactPosition[i], m_contactNormal);
        angularInertiaWorld = inverseInertiaTensor * angularInertiaWorld;
        angularInertiaWorld = glm::cross(angularInertiaWorld, m_relativeContactPosition[i]);
        angularInertia[i] = glm::dot(angularInertiaWorld, m_contactNormal);

        linearInertia[i] = m_body[i]->m_inverseMass;

        totalInertia += linearInertia[i] + angularInertia[i];
    }

    for (size_t i = 0; i < 2; i++)
    {
        if (!m_body[i])
            continue;
        float sign = (i == 0) ? 1 : -1;
        angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
        linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

        glm::vec3 projection = m_relativeContactPosition[i];
        projection += m_contactNormal * glm::dot(-m_relativeContactPosition[i], m_contactNormal);

        float maxMagnitude = angularLimit * glm::length(projection);

        if (angularMove[i] < -maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = -maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }
        else if (angularMove[i] > maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }

        if (angularMove[i] == 0)
        {
            angularChange[i] = glm::vec3(0);
        }
        else
        {
            glm::vec3 targetAngularDirection = glm::cross(m_relativeContactPosition[i], m_contactNormal);
            glm::mat3 inverseInertiaTensor = m_body[i]->m_invInertiaTensorWorld;

            angularChange[i] = inverseInertiaTensor * targetAngularDirection * (angularMove[i] / angularInertia[i]);
        }

        linearChange[i] = m_contactNormal * linearMove[i];

        Transform* transform = m_body[i]->m_entity->GetComponent<Transform>();
        transform->addPosition(linearChange[i]);
        transform->addRotation(angularChange[i]); 
    }
}


void Contact::applyVelocityChange(glm::vec3 velocityChange[2], glm::vec3 rotationChange[2])
{
    glm::mat3 inverseInertiaTensor[2];
    inverseInertiaTensor[0] = m_body[0]->m_invInertiaTensorWorld;
    if (m_body[1])
        inverseInertiaTensor[1] = m_body[1]->m_invInertiaTensorWorld;

    glm::vec3 impulseContact;

    if (m_friction == 0.0f)
    {
        impulseContact = calculateFrictionlessImpulse();
    }
    else
    {
        impulseContact = calculateFrictionImpulse();
    }
    glm::vec3 impulse = m_contactToWorld * impulseContact;
    glm::vec3 impulsiveTorque = glm::cross(m_relativeContactPosition[0], impulse);
    rotationChange[0] = inverseInertiaTensor[0] * impulsiveTorque;
    velocityChange[0] = impulse * m_body[0]->m_inverseMass;

    m_body[0]->m_velocity += velocityChange[0];
    m_body[0]->m_angularVelocity += rotationChange[0];

    if (m_body[1])
    {
        glm::vec3 impulsiveTorque = glm::cross(impulse, m_relativeContactPosition[1]);
        rotationChange[1] = inverseInertiaTensor[1] * impulsiveTorque;
        velocityChange[1] = glm::vec3(0.0f);
        velocityChange[1] += impulse * -m_body[1]->m_inverseMass;

        m_body[1]->m_velocity += velocityChange[1];
        m_body[1]->m_angularVelocity += rotationChange[1];
    }
}

glm::vec3 Contact::calculateFrictionlessImpulse()
{
    glm::vec3 deltaVelWorld = glm::cross(m_relativeContactPosition[0], m_contactNormal);
    deltaVelWorld = m_body[0]->m_invInertiaTensorWorld * deltaVelWorld;
    deltaVelWorld = glm::cross(deltaVelWorld, m_relativeContactPosition[0]);
    
    float deltaVelocity = glm::dot(deltaVelWorld, m_contactNormal);
    deltaVelocity += m_body[0]->m_inverseMass;
    
    if (m_body[1])
    {
        glm::vec3 deltaVelWorld = glm::cross(m_relativeContactPosition[1], m_contactNormal);
        deltaVelWorld = m_body[1]->m_invInertiaTensorWorld * deltaVelWorld;
        deltaVelWorld = glm::cross(deltaVelWorld, m_relativeContactPosition[1]);

        deltaVelocity += glm::dot(deltaVelWorld, m_contactNormal);
        deltaVelocity += m_body[1]->m_inverseMass;
    }

    glm::vec3 impulseContact = glm::vec3(
        m_desiredDeltaVelocity / deltaVelocity,
        0.0f,
        0.0f
    );
    return impulseContact;
}

glm::vec3 Contact::calculateFrictionImpulse()
{
    glm::vec3 impulseContact;
    float inverseMass = m_body[0]->m_inverseMass;

    glm::mat3 impulseToTorque(
        0.0f, m_relativeContactPosition[0].z, -m_relativeContactPosition[0].y,
        -m_relativeContactPosition[0].z, 0.0f, m_relativeContactPosition[0].x,
        m_relativeContactPosition[0].y, -m_relativeContactPosition[0].x, 0.0f
    );

    glm::mat3 deltaVelWorld = impulseToTorque;
    deltaVelWorld *= m_body[0]->m_invInertiaTensorWorld;
    deltaVelWorld *= impulseToTorque;
    deltaVelWorld *= -1;

    if (m_body[1])
    {
        inverseMass += m_body[1]->m_inverseMass;

        glm::mat3 impulseToTorque(
            0.0f, m_relativeContactPosition[1].z, -m_relativeContactPosition[1].y,
            -m_relativeContactPosition[1].z, 0.0f, m_relativeContactPosition[1].x,
            m_relativeContactPosition[1].y, -m_relativeContactPosition[1].x, 0.0f
        );

        glm::mat3 deltaVelWorld2 = impulseToTorque;
        deltaVelWorld2 *= m_body[1]->m_invInertiaTensorWorld;
        deltaVelWorld2 *= impulseToTorque;
        deltaVelWorld2 *= -1;

        deltaVelWorld += deltaVelWorld2;
    }

    glm::mat3 deltaVelocity = glm::transpose(m_contactToWorld);
    deltaVelocity *= deltaVelWorld;
    deltaVelocity *= m_contactToWorld;

    deltaVelocity[0][0] += inverseMass;
    deltaVelocity[1][1] += inverseMass;
    deltaVelocity[2][2] += inverseMass;

    glm::mat3 impulseMatrix = glm::inverse(deltaVelocity);

    // This vector is used for static friction.
    glm::vec3 velKill(m_desiredDeltaVelocity, -m_contactVelocity.y, -m_contactVelocity.z);

    impulseContact = impulseMatrix * velKill;

    float planarImpulse = sqrt(impulseContact.y * impulseContact.y + impulseContact.z * impulseContact.z);
    
    // If the static friction is bigger than the normal force then it is a dynamic friction.
    if (planarImpulse > impulseContact.x * m_friction)
    {
        // Limit friction
        impulseContact.y /= planarImpulse;
        impulseContact.z /= planarImpulse;

        // Recalculate impulse in the normal direction.
        impulseContact.x = deltaVelocity[0][0] +
            deltaVelocity[1][0] * m_friction * impulseContact.y +
            deltaVelocity[2][0] * m_friction * impulseContact.z;
        impulseContact.x = m_desiredDeltaVelocity / impulseContact.x;
        impulseContact.y *= m_friction * impulseContact.x;
        impulseContact.z *= m_friction * impulseContact.x;
    }
    return impulseContact;
}