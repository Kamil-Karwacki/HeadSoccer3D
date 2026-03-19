#include "collider.hpp"

void Collider::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (transform == nullptr)
        std::cerr << "Warning: Collider requires transform component!\n";
}