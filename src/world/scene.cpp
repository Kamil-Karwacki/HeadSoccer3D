#include "scene.hpp"
#include "graphics/model.hpp"
#include "components/meshRenderer.hpp"
#include "components/playerController.hpp"
#include "components/collider.hpp"
#include "core/application.hpp"
#include "core/debug.hpp"

void Scene::init()
{
    Model tempMesh(PROJECT_DIR "assets/models/model.obj");

    Entity* player = new Entity();
    player->AddComponent<Transform>();
    player->AddComponent<PlayerController>();
    
    Entity* tempObject = new Entity();
    tempObject->AddComponent<Transform>();
    tempObject->AddComponent<MeshRenderer>(std::make_shared<Model>(tempMesh));

    Transform* tempObjectTransform = tempObject->GetComponent<Transform>();
    tempObjectTransform->setScale(glm::vec3(10.1f, 10.1f, 10.1f));
    tempObjectTransform->setPosition(glm::vec3(15.0f, 15.0f, 15.0f));

    m_entities.push_back(std::unique_ptr<Entity>(player));
    m_entities.push_back(std::unique_ptr<Entity>(tempObject));

    Entity* box = new Entity();
    box->AddComponent<Transform>();
    box->AddComponent<MeshRenderer>(std::make_shared<Model>(Mesh::createBox(glm::vec3(55.0f, 1.0f, 54.0f), glm::vec3(0.2f, 0.5f, 0.2f))));
    box->AddComponent<PlaneCollider>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
    m_entities.push_back(std::unique_ptr<Entity>(box));

    Entity* sphere = new Entity();
    sphere->AddComponent<Transform>();
    sphere->AddComponent<MeshRenderer>(std::make_shared<Model>(PROJECT_DIR "assets/models/sphere.obj"));
    sphere->GetComponent<Transform>()->setScale(glm::vec3(2.0f));
    sphere->GetComponent<Transform>()->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    sphere->AddComponent<SphereCollider>(2.0f);
    sphere->AddComponent<Rigidbody>();
    m_entities.push_back(std::unique_ptr<Entity>(sphere));

    Entity* boxTwo = new Entity();
    boxTwo->AddComponent<Transform>();
    boxTwo->AddComponent<MeshRenderer>(std::make_shared<Model>(Mesh::createBox(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.8f, 0.2f, 0.2f))));
    boxTwo->GetComponent<Transform>()->setPosition(glm::vec3(4.0f, 2.0f, 1.0f));
    boxTwo->AddComponent<BoxCollider>(glm::vec3(2.5f, 2.5f, 2.5f));
    boxTwo->AddComponent<Rigidbody>();
    m_entities.push_back(std::unique_ptr<Entity>(boxTwo));

    m_mainPlayer = player->GetComponent<PlayerController>();

    std::cout << "Scene initialized successfully\n";
}

void Scene::update(float deltaTime)
{
    for (auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }
}

void Scene::fixedUpdate(float deltaTime)
{
    for (auto& entity : m_entities)
    {
        m_physicsSystem.generateContacts(m_entities);
    }
}


void Scene::draw()
{
    for (auto& entity : m_entities)
    {
        entity->draw();
    }
}

glm::mat4 Scene::getMainViewMatrix() const 
{
    return m_mainPlayer ? m_mainPlayer->getViewMatrix() : glm::mat4(1.0f); 
}

glm::mat4 Scene::getMainProjectionMatrix() const
{
    return m_mainPlayer ? m_mainPlayer->getProjectionMatrix() : glm::mat4(1.0f);
}