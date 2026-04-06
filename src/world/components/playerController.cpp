#include <glad/glad.h>
#include "playerController.hpp"
#include "core/application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void PlayerController::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (!transform)
        std::cerr << "Error: PlayerController requires transform component!\n";
}

void PlayerController::update(float deltaTime)
{
    Transform* transform = m_entity->GetComponent<Transform>();

    if (!transform)
        return;
    
    float speed = 20.0f;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Application& app = Application::Get();

    InputManager manager = app.GetInput();
    if (manager.isActionHeld("forward"))
    {
        transform->setPosition(transform->getPosition() + m_front * deltaTime * speed);
    }
    if (manager.isActionHeld("back"))
    {
        transform->setPosition(transform->getPosition() - m_front * deltaTime * speed);
    }
    if (manager.isActionHeld("left"))
    {
        transform->setPosition(transform->getPosition() - glm::cross(m_front, up) * deltaTime * speed);
    }
    if (manager.isActionHeld("right"))
    {
        transform->setPosition(transform->getPosition() + glm::cross(m_front, up) * deltaTime * speed);
    }

    float mouseDeltaX = static_cast<float>(manager.getMouseDeltaX());
    float mouseDeltaY = static_cast<float>(manager.getMouseDeltaY());

    float mouseSensitivity = 0.001f;
    m_yaw += mouseDeltaX * mouseSensitivity;
    m_pitch += mouseDeltaY * mouseSensitivity;

    m_pitch = glm::clamp(m_pitch, -1.5f, 1.5f);

    transform->setRotation(glm::vec3(m_pitch, -m_yaw, 0.0f));
}
