#include <glad/glad.h>
#include "playerController.hpp"
#include "core/application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void PlayerController::start()
{
    m_transform = entity->GetComponent<Transform>();
    
    if (m_transform == nullptr)
    {
        std::cerr << "Warning: PlayerController requires transform component!\n";
    }
    
}

void PlayerController::update(float deltaTime)
{
    if (!m_transform)
        return;
    
    float speed = 20.0f;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    Application& app = Application::Get();

    InputManager manager = app.GetInput();
    if (manager.isActionHeld("forward"))
    {
        m_transform->m_position += m_front * deltaTime * speed;
    }
    if (manager.isActionHeld("back"))
    {
        m_transform->m_position -= m_front * deltaTime * speed;
    }
    if (manager.isActionHeld("left"))
    {
        m_transform->m_position -= glm::cross(m_front, up) * deltaTime * speed;
    }
    if (manager.isActionHeld("right"))
    {
        m_transform->m_position += glm::cross(m_front, up) * deltaTime * speed;
    }

    float mouseDeltaX = static_cast<float>(manager.getMouseDeltaX());
    float mouseDeltaY = static_cast<float>(manager.getMouseDeltaY());

    float mouseSensitivity = 0.1f;
    m_transform->m_rotation.x += mouseDeltaX * mouseSensitivity;
    m_transform->m_rotation.y += mouseDeltaY * mouseSensitivity;


    std::shared_ptr<Shader> defaultShader = app.getShader("default");

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
    static_cast<float>(app.getWindowWidth()) / static_cast<float>(app.getWindowHeight()), 0.1f, 100.0f);
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, m_transform->m_position);
    view = GetViewMatrix();

    defaultShader->setMat4("view", 1, GL_FALSE, &view[0][0]);
    defaultShader->setMat4("projection", 1, GL_FALSE, &projection[0][0]);
}

glm::mat4 PlayerController::GetViewMatrix()
{
    if (m_transform->m_rotation.y > 89.0f)  m_transform->m_rotation.y = 89.0f;
    if (m_transform->m_rotation.y < -89.0f) m_transform->m_rotation.y = -89.0f;

    float yawRads = glm::radians(m_transform->m_rotation.x);
    float pitchRads = glm::radians(m_transform->m_rotation.y);

    m_front.x = cos(yawRads) * cos(pitchRads);
    m_front.y = sin(pitchRads);
    m_front.z = sin(yawRads) * cos(pitchRads);
    
    m_front = glm::normalize(m_front);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    return glm::lookAt(m_transform->m_position, m_transform->m_position + m_front, up);
}