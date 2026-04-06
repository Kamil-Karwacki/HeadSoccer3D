#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include "graphics/model.hpp"

class MeshRenderer : public Component
{
public:
    virtual ~MeshRenderer() override = default;

    MeshRenderer(std::shared_ptr<Model> mesh, glm::vec3 offset = {0, 0, 0}) : 
    m_model(mesh), m_offset(offset) { }

    void start() override;
    void draw() override;

    glm::vec3 m_offset;
private:
    std::shared_ptr<Model> m_model = nullptr;
};