#include "physicsSystem.hpp"
#include "world/component.hpp"
#include "world/components/transform.hpp"

bool PhysicsSystem::sphereAndSphere(const SphereCollider& one, const SphereCollider& two)
{
    Transform* transform1 = one.m_entity->GetComponent<Transform>();
    Transform* transform2 = two.m_entity->GetComponent<Transform>();
    if (transform1 == nullptr || transform2 == nullptr)
        std::cerr << "Error: Collider needs to have attached transform component\n";

    glm::vec3 positionOne = transform1->getPosition() + glm::vec3(one.m_offset[3]);
    glm::vec3 positionTwo = transform2->getPosition() + glm::vec3(two.m_offset[3]);

    glm::vec3 midline = positionOne - positionTwo;
    float size = midline.length();

    if (size <= 0.0f || size >= one.m_radius + two.m_radius)
        return false;

    glm::vec3 normal = midline * (1.0f / size);

    Contact contact;
    contact.m_contactNormal = normal;
    contact.m_contactPoint = positionOne + midline * 0.5f;
    contact.m_penetration = (one.m_radius + two.m_radius - size);

    Rigidbody* rigidbody1 = one.m_entity->GetComponent<Rigidbody>();
    Rigidbody* rigidbody2 = two.m_entity->GetComponent<Rigidbody>();

    contact.m_body[0] = rigidbody1;
    contact.m_body[1] = rigidbody2;
    contact.m_restitution = (rigidbody1->restitution + rigidbody2->restitution) * 0.5f;
    contact.m_friction = (rigidbody1->friction + rigidbody2->friction) * 0.5f;
    m_contacts.push_back(contact);

    return true;
}
bool PhysicsSystem::sphereAndHalfspace(const SphereCollider& sphere, const PlaneCollider& plane)
{

    return true;
}

