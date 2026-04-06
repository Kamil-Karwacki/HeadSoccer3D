#pragma once
#include <vector>
#include "entity.hpp"
#include "physics/physicsSystem.hpp"
#include "components/playerController.hpp"
#include "world/components/camera.hpp"

class Scene
{
public:    
    Scene() = default;
    ~Scene() = default;
    virtual void init();
    void update(float deltaTime);
    void fixedUpdate(float deltaTime);
    void draw();

    glm::mat4 getMainViewMatrix() const;
    glm::mat4 getMainProjectionMatrix() const;
    void setMainCamera(Camera* camera) { m_mainCamera = camera; }

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    PhysicsSystem m_physicsSystem;
    Camera* m_mainCamera = nullptr;
};
