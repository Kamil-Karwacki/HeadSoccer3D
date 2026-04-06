#pragma once

class Entity; 

class Component
{
public:
    virtual ~Component() = default;

    Entity* m_entity = nullptr;
};