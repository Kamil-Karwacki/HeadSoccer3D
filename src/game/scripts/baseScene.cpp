#include "baseScene.hpp"

#include <memory>

#include "cameraController.hpp"
#include "core/application.hpp"
#include "core/debug.hpp"
#include "footballer.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "graphics/model.hpp"
#include "physics/physicsSystem.hpp"
#include "playerController.hpp"
#include "scripts/ball.hpp"
#include "world/components/collider.hpp"
#include "world/components/light.hpp"
#include "world/components/meshRenderer.hpp"
#include "world/components/rigidbody.hpp"
#include "world/components/transform.hpp"
#include "world/entity.hpp"
#include "world/scene.hpp"

void BaseScene::init()
{
    generateTerrain();
    Model tempMesh("assets/models/model.obj");

    Application &app = Application::Get();
    Shader *defaultShader = app.getShader("default");

    Entity &player = createEntity();
    player.AddComponent<Transform>(glm::vec3(0, 10, -19));
    player.AddComponent<PlayerController>();
    player.AddComponent<MeshRenderer>(
        std::make_shared<Model>("assets/models/sphere.obj"), defaultShader);
    player.AddComponent<PlayerController>();
    player.AddComponent<Rigidbody>(1.0f, 0.1f, 0.5f, 0.9f, 0.9f);
    player.AddComponent<SphereCollider>(2.0f);
    player.GetComponent<Rigidbody>()->m_invInertiaTensor =
        Rigidbody::createSphereInverseInertiaTensor(1.0f, 2.0f);
    player.AddComponent<Footballer>();

    glm::mat4 offset = glm::mat4(1.0f);
    offset = glm::translate(offset, glm::vec3(0, 0, 3));
    player.AddComponent<SphereCollider>(2.0f, offset, true);

    Entity &cameraPlayer = createEntity();
    cameraPlayer.AddComponent<Transform>();
    m_mainCamera = &cameraPlayer.AddComponent<Camera>();
    cameraPlayer.AddComponent<CameraController>(&player);

    Entity &sphere = createEntity();
    sphere.AddComponent<Transform>();
    sphere.AddComponent<MeshRenderer>(
        std::make_shared<Model>("assets/models/ball.obj"), defaultShader);
    sphere.GetComponent<Transform>()->setScale(glm::vec3(2.0f));
    sphere.GetComponent<Transform>()->setPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    sphere.AddComponent<SphereCollider>(2.0f);
    sphere.AddComponent<Rigidbody>(1.0f, 0.3f, 30.0f, 0.95f, 0.8f);
    Rigidbody *sphereRb = sphere.GetComponent<Rigidbody>();
    sphereRb->m_invInertiaTensor =
        Rigidbody::createSphereInverseInertiaTensor(10.0f, 2.0f);
    sphere.AddComponent<Ball>();

    Entity &sun = createEntity();
    sun.AddComponent<Transform>(glm::vec3(0, 50, 0),
                                glm::vec3(glm::radians(290.0f), 0, 0));
    sun.AddComponent<DirectionalLight>(glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.6f,
                                       0.4f);

    std::cout << "Scene initialized successfully\n";
}

void BaseScene::update(float deltaTime) { Scene::update(deltaTime); }

void BaseScene::fixedUpdate(float deltaTime)
{
    static constexpr float gravity = 350.0f;
    for (auto &entity : m_entities)
    {
        Rigidbody *rb = entity->GetComponent<Rigidbody>();
        if (rb)
        {
            rb->m_forceAcc += glm::vec3(0.0f, -1.0f, 0.0f) * gravity *
                              (1.0f / rb->m_inverseMass) * deltaTime;
        }
    }
    Scene::fixedUpdate(deltaTime);
}

void BaseScene::draw() { Scene::draw(); }

void BaseScene::generateTerrain()
{
    Application &app = Application::Get();
    Shader *defaultShader = app.getShader("default");

    glm::vec2 pitchSize = glm::vec2(115, 74);
    float wallHeight = 4.0f;
    float bannerLength = 32.0f;

    glm::vec2 tribuneOffset = glm::vec2(0, 10);
    glm::vec2 groundAdd = glm::vec2(tribuneOffset.y * 2);
    generatePitch(pitchSize, groundAdd, wallHeight, bannerLength,
                  defaultShader);
    glm::vec3 gateSize = glm::vec3(22.0f, 7.0f, 7.0f);
    float gateThickness = 0.7f;

    generateGates(pitchSize, gateSize, gateThickness, defaultShader);
    float tribuneLength = 32.0f;

    std::shared_ptr<Model> tribuneModel =
        std::make_shared<Model>("assets/models/tribune.obj");

    glm::vec2 tribuneCount = glm::round(pitchSize / tribuneLength);
    glm::vec2 tribunesLength = pitchSize / tribuneCount;
    glm::vec2 tribuneScale = tribunesLength / tribuneLength;

    for (size_t i = 0; i < tribuneCount.y; i++)
    {
        Entity &tribune = createEntity();
        tribune.AddComponent<Transform>(
            glm::vec3(pitchSize.y / 2.0f - tribunesLength.x / 2.0f -
                          tribunesLength.y * i,
                      0, pitchSize.x / 2.0f + tribuneOffset.y),
            glm::vec3(0, glm::radians(180.0f), 0),
            glm::vec3(tribuneScale.y, 1, 1));
        tribune.AddComponent<MeshRenderer>(tribuneModel, defaultShader);

        Entity &tribuneB = createEntity();
        tribuneB.AddComponent<Transform>(
            glm::vec3(pitchSize.y / 2.0f - tribunesLength.x / 2.0f -
                          tribunesLength.y * i,
                      0, -pitchSize.x / 2.0f - tribuneOffset.y),
            glm::vec3(0, 0, 0), glm::vec3(tribuneScale.y, 1, 1));
        tribuneB.AddComponent<MeshRenderer>(tribuneModel, defaultShader);
    }

    for (size_t i = 0; i < tribuneCount.x; i++)
    {
        Entity &tribuneA = createEntity();
        tribuneA.AddComponent<Transform>(
            glm::vec3(pitchSize.y / 2.0f + tribuneOffset.y, 0,
                      pitchSize.x / 2.0f - tribunesLength.x / 2.0f -
                          tribunesLength.x * i),
            glm::vec3(0, glm::radians(270.0f), 0),
            glm::vec3(tribuneScale.x, 1, 1));
        tribuneA.AddComponent<MeshRenderer>(tribuneModel, defaultShader);

        Entity &tribuneB = createEntity();
        tribuneB.AddComponent<Transform>(
            glm::vec3(-pitchSize.y / 2.0f - tribuneOffset.y, 0,
                      pitchSize.x / 2.0f - tribunesLength.x / 2.0f -
                          tribunesLength.x * i),
            glm::vec3(0, glm::radians(90.0f), 0),
            glm::vec3(tribuneScale.x, 1, 1));
        tribuneB.AddComponent<MeshRenderer>(tribuneModel, defaultShader);
    }
}

void BaseScene::generatePitch(glm::vec2 pitchSize, glm::vec2 groundAdd,
                              float wallHeight, float bannerLength,
                              Shader *defaultShader)
{

    Entity &ground = createEntity();
    ground.AddComponent<Transform>();
    ground.AddComponent<MeshRenderer>(
        std::make_shared<Model>(
            Mesh::createBox(glm::vec3(pitchSize.y + groundAdd.x, 0.1f,
                                      pitchSize.x + groundAdd.y),
                            glm::vec3(0.2f, 0.5f, 0.2f))),
        defaultShader);
    ground.AddComponent<HalfspaceCollider>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);

    std::shared_ptr<Model> bannerModelA =
        std::make_shared<Model>("assets/models/baner1.obj");
    glm::vec2 bannerCount = glm::round(pitchSize / bannerLength);
    glm::vec2 bannerLengths = pitchSize / bannerCount;
    glm::vec2 bannerScale = bannerLengths / bannerLength;
    for (size_t i = 0; i < bannerCount.y; i++)
    {
        // top
        Entity &wallA = createEntity();
        Transform &transA = wallA.AddComponent<Transform>();
        transA.setPosition(glm::vec3((pitchSize.y / 2.0f) -
                                         (bannerLengths.y / 2.0f) -
                                         bannerLengths.y * i,
                                     0.0f, pitchSize.x / 2.0f));
        transA.setScale(glm::vec3(bannerScale.y, 1.0f, 1.0f));
        transA.setRotation(
            glm::vec3(glm::radians(90.0f), glm::radians(180.0f), 0));
        wallA.AddComponent<MeshRenderer>(
            bannerModelA, defaultShader,
            glm::vec3(0.0f, wallHeight / 2.0f, 0.0f));
        if (i == 0)
            wallA.AddComponent<HalfspaceCollider>(glm::vec3(0.0f, 0.0f, -1.0f),
                                                  -pitchSize.x / 2.0f);

        // bottom
        Entity &wallB = createEntity();
        Transform &transB = wallB.AddComponent<Transform>();
        transB.setPosition(glm::vec3((pitchSize.y / 2.0f) -
                                         (bannerLengths.y / 2.0f) -
                                         bannerLengths.y * i,
                                     0.0f, -pitchSize.x / 2.0f));
        transB.setScale(glm::vec3(bannerScale.y, 1.0f, 1.0f));
        transB.setRotation(
            glm::vec3(glm::radians(90.0f), glm::radians(180.0f), 0));
        wallB.AddComponent<MeshRenderer>(
            bannerModelA, defaultShader,
            glm::vec3(0.0f, wallHeight / 2.0f, 0.0f));
        if (i == 0)
            wallB.AddComponent<HalfspaceCollider>(glm::vec3(0.0f, 0.0f, 1.0f),
                                                  -pitchSize.x / 2.0f);
    }

    for (size_t i = 0; i < bannerCount.x; i++)
    {
        // left
        Entity &wallA = createEntity();
        Transform &transA = wallA.AddComponent<Transform>();
        transA.setPosition(glm::vec3(pitchSize.y / 2.0f, 0.0f,
                                     (-pitchSize.x / 2.0f) +
                                         (bannerLengths.x / 2.0f) +
                                         bannerLengths.x * i));
        transA.setScale(glm::vec3(bannerScale.x, 1.0f, 1.0f));
        transA.setRotation(
            glm::vec3(glm::radians(90.0f), glm::radians(270.0f), 0));
        wallA.AddComponent<MeshRenderer>(
            bannerModelA, defaultShader,
            glm::vec3(0.0f, wallHeight / 2.0f, 0.0f));
        if (i == 0)
            wallA.AddComponent<HalfspaceCollider>(glm::vec3(-1.0f, 0.0f, 0.0f),
                                                  -pitchSize.y / 2.0f);

        // right
        Entity &wallB = createEntity();
        Transform &transB = wallB.AddComponent<Transform>();
        transB.setPosition(glm::vec3(-pitchSize.y / 2.0f, 0.0f,
                                     (-pitchSize.x / 2.0f) +
                                         (bannerLengths.x / 2.0f) +
                                         bannerLengths.x * i));
        transB.setScale(glm::vec3(bannerScale.x, 1.0f, 1.0f));
        transB.setRotation(
            glm::vec3(glm::radians(90.0f), glm::radians(90.0f), 0));
        wallB.AddComponent<MeshRenderer>(
            bannerModelA, defaultShader,
            glm::vec3(0.0f, wallHeight / 2.0f, 0.0f));
        if (i == 0)
            wallB.AddComponent<HalfspaceCollider>(glm::vec3(1.0f, 0.0f, 0.0f),
                                                  -pitchSize.y / 2.0f);
    }
}

void BaseScene::generateGates(glm::vec2 pitchSize, glm::vec3 gateSize,
                              float gateThickness, Shader *defaultShader)
{
    for (int j = 1; j > -2; j -= 2)
    {
        for (int i = 1; i > -2; i -= 2)
        {
            Entity &bar = createEntity();
            Transform &trans = bar.AddComponent<Transform>();
            trans.setPosition(
                glm::vec3(i * gateSize.x / 2.0f, gateSize.y / 2.0f,
                          j * pitchSize.x / 2.0f - gateSize.z * j));
            bar.AddComponent<MeshRenderer>(
                std::make_shared<Model>(Mesh::createBox(
                    glm::vec3(gateThickness, gateSize.y, gateThickness),
                    glm::vec3(0.8f, 0.8f, 0.8f))),
                defaultShader);
            bar.AddComponent<BoxCollider>(
                glm::vec3(gateThickness, gateSize.y, gateThickness));
        }
    }

    for (int i = 1; i > -2; i -= 2)
    {
        Entity &topBar = createEntity();
        Transform &topTrans = topBar.AddComponent<Transform>();
        topTrans.setPosition(glm::vec3(
            0.0f, gateSize.y, i * pitchSize.x / 2.0f - gateSize.z * i));
        topTrans.setRotation(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));
        topBar.AddComponent<MeshRenderer>(
            std::make_shared<Model>(Mesh::createBox(
                glm::vec3(gateThickness, gateSize.x + gateThickness,
                          gateThickness),
                glm::vec3(0.8f, 0.8f, 0.8f))),
            defaultShader);
        topBar.AddComponent<BoxCollider>(
            glm::vec3(gateThickness, gateSize.x, gateThickness));
    }
}
