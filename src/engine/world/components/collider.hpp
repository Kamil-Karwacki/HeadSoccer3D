#pragma once
#include <glm/glm.hpp>

#include "world/component.hpp"

struct Collider : public Component
{
   public:
    virtual ~Collider() override = default;

    glm::vec3 getAxis(int index) const;

    glm::mat4 m_offset = glm::mat4(1.0f);
    glm::mat4 m_worldTransform = glm::mat4(1.0f);
    bool m_isTrigger = false;
};

struct PlaneCollider : public Component
{
   public:
    PlaneCollider(const glm::vec3& normal, float offset) : m_normal(normal), m_offset(offset)
    {
    }

    glm::vec3 m_normal = glm::vec3(0.0f, 1.0f, 0.0f);
    float m_offset = 0.0f;
    bool m_isTrigger = false;
};

struct SphereCollider : public Collider
{
   public:
    SphereCollider(float radius = 1.0f) : m_radius(radius)
    {
    }

    float m_radius;
};

struct BoxCollider : public Collider
{
   public:
    BoxCollider(glm::vec3 halfSize = glm::vec3(1.0f)) : m_halfSize(halfSize)
    {
    }

    glm::vec3 m_halfSize;
};
