#include "playerController.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/application.hpp"
#include "scripts/footballer.hpp"
#include "world/components/rigidbody.hpp"
#include "world/components/transform.hpp"
#include "world/entity.hpp"

void PlayerController::onStart()
{
    Transform* transform = m_entity->GetComponent<Transform>();

    if (!transform) std::cerr << "Error: PlayerController requires transform component!\n";
}

void PlayerController::onUpdate(float deltaTime)
{
    /*
    Transform* transform = m_entity->GetComponent<Transform>();
    Rigidbody* rigidbody = m_entity->GetComponent<Rigidbody>();

    if (!transform || !rigidbody) return;

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
*/
    Footballer* footballer = m_entity->GetComponent<Footballer>();
    if (!footballer) return;

    Application& app = Application::Get();
    InputManager manager = app.GetInput();

    if (manager.isActionHeld("forward"))
    {
        footballer->m_input.y = 1;
    }
    if (manager.isActionHeld("back"))
    {
        footballer->m_input.y = -1;
    }
    if (manager.isActionHeld("left"))
    {
        footballer->m_input.x = -1;
    }
    if (manager.isActionHeld("right"))
    {
        footballer->m_input.x = 1;
    }
    if (manager.isActionPressed("space"))
    {
        footballer->kickBall();
    }
}
