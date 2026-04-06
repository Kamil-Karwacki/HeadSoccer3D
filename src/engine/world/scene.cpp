#include "scene.hpp"
#include "graphics/model.hpp"
#include "components/meshRenderer.hpp"
#include "components/collider.hpp"
#include "core/application.hpp"
#include "core/debug.hpp"

void Scene::init()
{
}

void Scene::update(float deltaTime)
{
    for (Behaviour* behaviour : m_activeBehaviours)
    {
        behaviour->onUpdate(deltaTime);
    }
}

void Scene::fixedUpdate(float deltaTime)
{
    static constexpr float gravity = 350.0f;
    for (auto& entity : m_entities)
    {
        Rigidbody* rb = entity->GetComponent<Rigidbody>();
        if(rb)
        {
            rb->integrate(deltaTime);
            rb->addForce(glm::vec3(0.0f,-1.0f,0.0f) * gravity * rb->getMass() * deltaTime);
        }
        m_physicsSystem.generateContacts(m_entities);
        m_physicsSystem.resolveContacts(deltaTime);
    }
}


void Scene::draw()
{
    m_renderSystem.render(m_entities, m_mainCamera->m_entity);
}

glm::mat4 Scene::getMainViewMatrix() const 
{
    return m_mainCamera ? glm::inverse(m_mainCamera->m_entity->GetComponent<Transform>()->getModelMatrix()) : glm::mat4(1.0f); 
}

glm::mat4 Scene::getMainProjectionMatrix() const
{
    return m_mainCamera ? m_mainCamera->getProjection() : glm::mat4(1.0f);
}

Entity& Scene::createEntity()
{
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(this);

    Entity* rawPtr = entity.get();
    m_entities.push_back(std::move(entity));

    return *rawPtr;
}