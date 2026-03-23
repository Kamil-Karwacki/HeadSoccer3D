#pragma once
#include <vector>
#include "entity.hpp"
#include "physics/physicsSystem.hpp"
#include "components/playerController.hpp"


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
    void setMainPlayer(PlayerController* player) { m_mainPlayer = player; }

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    PhysicsSystem m_physicsSystem;
    PlayerController* m_mainPlayer = nullptr;
};
