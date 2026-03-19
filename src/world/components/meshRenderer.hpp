#pragma once
#include "world/entity.hpp"
#include "world/component.hpp"
#include "transform.hpp"
#include "graphics/model.hpp"

class MeshRenderer : public Component
{
private:
    std::shared_ptr<Model> m_mesh = nullptr;

public:
    MeshRenderer(std::shared_ptr<Model> mesh) : m_mesh(mesh) { }

    void start() override;
    void draw() override;
};