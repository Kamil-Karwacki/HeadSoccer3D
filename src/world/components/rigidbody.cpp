#include "rigidbody.hpp"

void Rigidbody::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    Collider* collider = m_entity->GetComponent<Collider>();
    
    if (transform == nullptr)
        std::cerr << "Error: Rigidbody requires transform component!\n";

    if (collider == nullptr)
        std::cerr << "Error: Rigidbody requires collider component!\n";
}