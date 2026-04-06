#include "camera.hpp"
#include "world/components/transform.hpp"
#include "core/application.hpp"

void Camera::start()
{

    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (!transform)
        std::cerr << "Error: Camera requires transform component!\n";

    Application& app = Application::Get();
    m_projection = glm::perspective(
        glm::radians(45.0f), static_cast<float>(app.getWindowWidth()) / 
        static_cast<float>(app.getWindowHeight()), 0.1f, 100.0f);
}

void Camera::update(float deltaTime)
{
    Application& app = Application::Get();
    std::shared_ptr<Shader> defaultShader = app.getShader("default");

    updateView();

    defaultShader->setMat4("view", 1, GL_FALSE, &m_view[0][0]);
    defaultShader->setMat4("projection", 1, GL_FALSE, &m_projection[0][0]);
}

void Camera::updateView()
{
    Transform* transform = m_entity->GetComponent<Transform>();

    m_front = transform->getRotation() * glm::vec3(0.0f, 0.0f, -1.0f);
    m_front = glm::normalize(m_front);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_view = glm::mat4(1.0f);
    m_view = glm::translate(m_view, transform->getPosition());
    m_view = glm::lookAt(transform->getPosition(), transform->getPosition() + m_front, up);
}