#pragma once
#include <vector>
#include "entity.hpp"
#include "physics/physicsSystem.hpp"
#include "world/components/camera.hpp"
#include "graphics/renderSystem.hpp"

class Scene
{
public:
    Scene(unsigned int whiteTextureId) : m_renderSystem(RenderSystem(whiteTextureId))
    {}
    virtual ~Scene() = default;
    virtual void init();
    virtual void update(float deltaTime);
    virtual void fixedUpdate(float deltaTime);
    virtual void draw();

    glm::mat4 getMainViewMatrix() const;
    glm::mat4 getMainProjectionMatrix() const;
    void setMainCamera(Camera* camera) { m_mainCamera = camera; }

    Entity& createEntity();
    
    void addBehaviour(Behaviour* behaviour) { m_activeBehaviours.push_back(behaviour); }

protected:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<Behaviour*> m_activeBehaviours;

    PhysicsSystem m_physicsSystem;
    RenderSystem m_renderSystem;
    Camera* m_mainCamera = nullptr;
};
