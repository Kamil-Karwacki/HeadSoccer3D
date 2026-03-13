#include "entity.hpp"

void Entity::update(float deltaTime)
{
    for (auto& component : m_components)
    {
        component->update(deltaTime);
    }
}

void Entity::draw()
{
    for (auto& component : m_components)
    {
        component->draw();
    }
}