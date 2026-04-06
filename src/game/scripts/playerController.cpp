#include <glad/glad.h>
#include "playerController.hpp"
#include "core/application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void PlayerController::onStart()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (!transform)
        std::cerr << "Error: PlayerController requires transform component!\n";
}

void PlayerController::onUpdate(float deltaTime)
{
    Transform* transform = m_entity->GetComponent<Transform>();
    Rigidbody* rigidbody = m_entity->GetComponent<Rigidbody>();

    if (!transform || !rigidbody)
        return;
    
    static constexpr float speed = 2000.0f;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Application& app = Application::Get();

    InputManager manager = app.GetInput();

    glm::vec3 front = transform->getFront();
    if (manager.isActionHeld("forward"))
    {
        rigidbody->m_forceAcc += -front * deltaTime * speed;
    }
    if (manager.isActionHeld("back"))
    {
        rigidbody->m_forceAcc += front * deltaTime * speed;
    }
    if (manager.isActionHeld("left"))
    {
        rigidbody->m_forceAcc += glm::cross(front, up) * deltaTime * speed;
    }
    if (manager.isActionHeld("right"))
    {
        rigidbody->m_forceAcc += -glm::cross(front, up) * deltaTime * speed;
    }

    float mouseDeltaX = static_cast<float>(manager.getMouseDeltaX());

    float mouseSensitivity = 0.001f;
    m_yaw += mouseDeltaX * mouseSensitivity;

    transform->setRotation(glm::vec3(0.0f, -m_yaw, 0.0f));
}
