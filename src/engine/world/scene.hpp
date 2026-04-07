#pragma once
#include <memory>
#include <vector>

#include "world/components/camera.hpp"

class Entity;
class Behaviour;
class RenderSystem;
class PhysicsSystem;

class Scene
{
   public:
    Scene(unsigned int whiteTextureId);
    ~Scene();

    virtual void init();
    virtual void update(float deltaTime);
    virtual void fixedUpdate(float deltaTime);
    virtual void draw();

    glm::mat4 getMainViewMatrix() const;
    glm::mat4 getMainProjectionMatrix() const;
    void setMainCamera(Camera* camera)
    {
        m_mainCamera = camera;
    }

    Entity& createEntity();

    void addBehaviour(Behaviour* behaviour);

   protected:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::vector<Behaviour*> m_activeBehaviours;

    std::unique_ptr<PhysicsSystem> m_physicsSystem;
    std::unique_ptr<RenderSystem> m_renderSystem;
    Camera* m_mainCamera = nullptr;
};
