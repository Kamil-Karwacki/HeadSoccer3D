#include "baseScene.hpp"
#include "graphics/model.hpp"
#include "world/scene.hpp"
#include "world/components/meshRenderer.hpp"
#include "world/components/collider.hpp"
#include "core/application.hpp"
#include "core/debug.hpp"
#include "playerController.hpp"
#include "cameraController.hpp"

void BaseScene::init()
{
    Model tempMesh(PROJECT_DIR "assets/models/model.obj");

    Application& app = Application::Get();
    Shader* defaultShader = app.getShader("default");

    Entity& player = createEntity(); 
    player.AddComponent<Transform>(glm::vec3(0, 3, 20));
    player.AddComponent<PlayerController>(); 
    player.AddComponent<MeshRenderer>(std::make_shared<Model>(PROJECT_DIR "assets/models/sphere.obj"), defaultShader);
    player.AddComponent<PlayerController>();
    player.AddComponent<Rigidbody>(1.0f, 0.1f, 0.5f, 0.9f, 0.9f);
    player.AddComponent<SphereCollider>(2.0f);
    player.GetComponent<Rigidbody>()->setInverseInertiaTensor(Rigidbody::createSphereInverseInertiaTensor(1.0f, 2.0f));

    Entity& cameraPlayer = createEntity();
    cameraPlayer.AddComponent<Transform>();
    m_mainCamera = &cameraPlayer.AddComponent<Camera>();
    cameraPlayer.AddComponent<CameraController>(&player);

    Entity& tempObject = createEntity();
    tempObject.AddComponent<Transform>();
    tempObject.AddComponent<MeshRenderer>(std::make_shared<Model>(tempMesh), defaultShader);

    Transform* tempObjectTransform = tempObject.GetComponent<Transform>();
    tempObjectTransform->setScale(glm::vec3(10.1f, 10.1f, 10.1f));
    tempObjectTransform->setPosition(glm::vec3(15.0f, 15.0f, 15.0f));

    Entity& box = createEntity();
    box.AddComponent<Transform>();
    box.AddComponent<MeshRenderer>(std::make_shared<Model>(Mesh::createBox(glm::vec3(55.0f, 1.0f, 54.0f), glm::vec3(0.2f, 0.5f, 0.2f))), defaultShader);
    box.AddComponent<PlaneCollider>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

    Entity& sphere = createEntity();
    sphere.AddComponent<Transform>();
    sphere.AddComponent<MeshRenderer>(std::make_shared<Model>(PROJECT_DIR "assets/models/sphere.obj"), defaultShader);
    sphere.GetComponent<Transform>()->setScale(glm::vec3(2.0f));
    sphere.GetComponent<Transform>()->setPosition(glm::vec3(0.0f, 22.0f, 0.0f));
    sphere.AddComponent<SphereCollider>(2.0f);
    sphere.AddComponent<Rigidbody>(10.0f, 0.3f, 30.0f, 0.85f, 0.8f);
    Rigidbody* sphereRb = sphere.GetComponent<Rigidbody>();
    sphereRb->setInverseInertiaTensor(Rigidbody::createSphereInverseInertiaTensor(10.0f, 2.0f));

    /*Entity* sphere2 = new Entity();
    sphere2->AddComponent<Transform>();
    sphere2->AddComponent<MeshRenderer>(std::make_shared<Model>(PROJECT_DIR "assets/models/sphere.obj"));
    sphere2->GetComponent<Transform>()->setScale(glm::vec3(2.0f));
    sphere2->GetComponent<Transform>()->setPosition(glm::vec3(1.0f, 3.0f, 0.0f));
    sphere2->AddComponent<SphereCollider>(2.0f);
    sphere2->AddComponent<Rigidbody>(10.0f, 0.3f, 0.0f);
    m_entities.push_back(std::unique_ptr<Entity>(sphere2));*/
    Entity& boxTwo = createEntity();
    boxTwo.AddComponent<Transform>();
    boxTwo.AddComponent<MeshRenderer>(std::make_shared<Model>(Mesh::createBox(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.8f, 0.2f, 0.2f))), defaultShader);
    boxTwo.GetComponent<Transform>()->setPosition(glm::vec3(4.0f, 6.0f, 1.0f));
    boxTwo.GetComponent<Transform>()->setRotation(glm::vec3(3));
    boxTwo.AddComponent<BoxCollider>(glm::vec3(2.5f, 2.5f, 2.5f));
    boxTwo.AddComponent<Rigidbody>(10.0f, 0.3f, 3.0f, 0.5f, 0.5f);
    Rigidbody* boxRb = boxTwo.GetComponent<Rigidbody>();
    boxRb->setInverseInertiaTensor(Rigidbody::createBoxInverseInertiaTensor(boxRb->getMass(), 5.0f, 5.0f, 5.0f));

    std::cout << "Scene initialized successfully\n";
}

void BaseScene::update(float deltaTime)
{
    Scene::update(deltaTime);
}

void BaseScene::fixedUpdate(float deltaTime)
{
    Scene::fixedUpdate(deltaTime);
}

void BaseScene::draw()
{
    Scene::draw();
}