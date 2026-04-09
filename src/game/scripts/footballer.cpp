#include "footballer.hpp"

#include "core/application.hpp"
#include "core/debug.hpp"
#include "glm/geometric.hpp"
#include "world/components/collider.hpp"
#include "world/components/rigidbody.hpp"
#include "world/components/transform.hpp"
#include "world/entity.hpp"
void Footballer::onUpdate(float deltaTime)
{
    m_ball = nullptr;
    move(deltaTime);
}

void Footballer::onTriggerEnter(Collider* other)
{
    detectBall(other);
}

void Footballer::detectBall(Collider* other)
{
    m_ball = other->m_entity->GetComponent<Ball>();
}

void Footballer::kickBall()
{
    if (!m_ball) return;
    Rigidbody* ballRb = m_ball->m_entity->GetComponent<Rigidbody>();
    if (!ballRb) return;
    Transform* ballTrans = m_ball->m_entity->GetComponent<Transform>();
    if (!ballTrans) return;

    Transform* transform = m_entity->GetComponent<Transform>();
    Debug::addLine(transform->getPosition(), transform->getPosition() + glm::vec3(0, 4, 0));

    Application& app = Application::Get();
    InputManager manager = app.GetInput();

    if (manager.isActionPressed("space"))
    {
        glm::vec3 kickDir = glm::normalize(
            (ballTrans->getPosition() + glm::vec3(0.0f, 3.0f, 0.0f)) - transform->getPosition());
        ballRb->m_forceAcc += m_kickStrength * kickDir;
    }
}

void Footballer::move(float deltaTime)
{
    Transform* transform = m_entity->GetComponent<Transform>();
    Rigidbody* rigidbody = m_entity->GetComponent<Rigidbody>();

    if (!transform || !rigidbody) return;

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 front = transform->getFront();

    rigidbody->m_forceAcc += -front * deltaTime * m_speed * rigidbody->getMass() * m_input.y;
    rigidbody->m_forceAcc +=
        -glm::cross(front, up) * deltaTime * m_speed * rigidbody->getMass() * m_input.x;

    transform->setRotation(glm::vec3(0.0f, -m_angularInput, 0.0f));
    m_input = glm::vec2(0.0f, 0.0f);
    m_angularInput = 0.0f;
}
