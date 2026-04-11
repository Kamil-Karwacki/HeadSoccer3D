#pragma once
#include <memory>

#include "graphics/model.hpp"
#include "world/component.hpp"

class MeshRenderer : public Component
{
   public:
    virtual ~MeshRenderer() override = default;

    MeshRenderer(std::shared_ptr<Model> mesh, Shader* shader, glm::vec3 offset = {0, 0, 0})
        : m_model(mesh), m_offset(offset), m_shader(shader)
    {
    }

    glm::vec3 m_offset;
    std::shared_ptr<Model> m_model = nullptr;
    Shader* m_shader = nullptr;
};
