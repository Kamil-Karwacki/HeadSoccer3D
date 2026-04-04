#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include "graphics/model.hpp"

class MeshRenderer : public Component
{
private:
    std::shared_ptr<Model> m_model = nullptr;

public:
    glm::vec3 m_offset;
    MeshRenderer(std::shared_ptr<Model> mesh, glm::vec3 offset = {0, 0, 0}) : 
    m_model(mesh), m_offset(offset) { }

    void start() override;
    void draw() override;
};