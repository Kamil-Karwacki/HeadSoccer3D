#pragma once
#include "world/component.hpp"
#include <glm/glm.hpp>
#include <iostream>
class Transform : public Component 
{
public:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale{1, 1, 1};
};