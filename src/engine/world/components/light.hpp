#pragma once

#include "world/component.hpp"
#include <glm/glm.hpp>

enum class LightType
{
    Directional,
    Point,
    Spot
};

struct DirectionalLight : public Component
{
    DirectionalLight() = default;
    DirectionalLight(glm::vec3 color, float ambient, float diffuse,
                     float specular)
        : m_color(color), m_ambient(ambient), m_diffuse(diffuse),
          m_specular(specular)
    {
    }

    glm::vec3 m_color = glm::vec3(1.0f);
    float m_ambient = 0.1f;
    float m_diffuse = 0.8f;
    float m_specular = 0.5f;
};

struct PointLight : public Component
{
    glm::vec3 m_color = glm::vec3(1.0f);
    float m_intensity = 1.0f;
    float m_radius = 10.0f;

    float m_constant = 1.0f;
    float m_linear = 0.09f;
    float m_quadratic = 0.032f;
};

struct SpotLight : public Component
{
    glm::vec3 m_color = glm::vec3(1.0f);
    float m_intensity = 1.0f;
    float m_cutOff = glm::cos(glm::radians(12.5f));
    float m_outerCutOff = glm::cos(glm::radians(15.0f));
};
