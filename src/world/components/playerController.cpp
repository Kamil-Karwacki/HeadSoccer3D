#include <glad/glad.h>
#include "playerController.hpp"
#include "core/application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void PlayerController::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (transform == nullptr)
        std::cerr << "Error: PlayerController requires transform component!\n";
    
    Application& app = Application::Get();
    m_projection = glm::perspective(
        glm::radians(45.0f), static_cast<float>(app.getWindowWidth()) / 
        static_cast<float>(app.getWindowHeight()), 0.1f, 100.0f);
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

    float mouseSensitivity = 0.1f;
    transform->setRotation(glm::vec3(
        transform->getRotation().x + mouseDeltaX * mouseSensitivity,
        transform->getRotation().y,
        transform->getRotation().z
    ));

    transform->setRotation(glm::vec3(
        transform->getRotation().x,
        transform->getRotation().y + mouseDeltaY * mouseSensitivity,
        transform->getRotation().z
    ));

    std::shared_ptr<Shader> defaultShader = app.getShader("default");

    glm::mat4 view = getViewMatrix();

    defaultShader->setMat4("view", 1, GL_FALSE, &view[0][0]);
    defaultShader->setMat4("projection", 1, GL_FALSE, &m_projection[0][0]);
}

glm::mat4 PlayerController::getViewMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    Transform* transform = m_entity->GetComponent<Transform>();

    glm::vec3 rotation = transform->getRotation();

    if (rotation.y > 89.0f) transform->setRotation(glm::vec3(rotation.x, 89.0f, rotation.z));
    if (rotation.y < -89.0f) transform->setRotation(glm::vec3(rotation.x, -89.0f, rotation.z));

    rotation = transform->getRotation();
    float yawRads = glm::radians(rotation.x);
    float pitchRads = glm::radians(rotation.y);

    m_front.x = cos(yawRads) * cos(pitchRads);
    m_front.y = sin(pitchRads);
    m_front.z = sin(yawRads) * cos(pitchRads);
    
    m_front = glm::normalize(m_front);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    view = glm::translate(view, transform->getPosition());
    view = glm::lookAt(transform->getPosition(), transform->getPosition() + m_front, up);
    return view;
}

glm::mat4 PlayerController::getProjectionMatrix()
{
    return m_projection;
}
