#include "scene.hpp"
#include "graphics/model.hpp"
#include "components/meshRenderer.hpp"
#include "components/playerController.hpp"

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
    tempObjectTransform->m_scale = glm::vec3(10.1f,10.1f,10.1f);

    m_entities.push_back(std::unique_ptr<Entity>(player));
    m_entities.push_back(std::unique_ptr<Entity>(tempObject));

    std::cout << "Scene initialized successfully\n";
}

void Scene::update(float deltaTime)
{
    for (auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }
}

void Scene::draw()
{
    for (auto& entity : m_entities)
    {
        entity->draw();
    }
}