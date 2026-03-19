#pragma once
#include "contact.hpp"
#include "world/components/collider.hpp"

class PhysicsSystem
{
public:
    bool sphereAndSphere(const SphereCollider& one, const SphereCollider& two);
    //bool boxAndSphere(const BoxCollider& box, const SphereCollider& sphere);
    bool sphereAndHalfspace(const SphereCollider& sphere, const PlaneCollider& plane);

private:
    std::vector<Contact> m_contacts;

};
