#include "renderSystem.hpp"
#include <glm/glm.hpp>
#include "world/components/meshRenderer.hpp"
#include "world/components/transform.hpp"

void RenderSystem::render(std::vector<std::unique_ptr<Entity>>& entities, Entity *cameraEntity)
{
    if (!cameraEntity) return;
    Camera* camera = cameraEntity->GetComponent<Camera>();
    Transform* cameraTransform = cameraEntity->GetComponent<Transform>();
    if (!camera || !cameraTransform) return;
    
    glm::mat4 projection = camera->getProjection();
    glm::mat4 view = glm::inverse(cameraTransform->getModelMatrix());
    
    for (const std::unique_ptr<Entity>& entity : entities) 
    {
        MeshRenderer* renderer = entity->GetComponent<MeshRenderer>();
        Transform* transform = entity->GetComponent<Transform>();

        if (!renderer || !transform)
            continue;

        renderer->m_shader->use();

        renderer->m_shader->setMat4("projection", 1, GL_FALSE, &projection[0][0]);
        renderer->m_shader->setMat4("view", 1, GL_FALSE, &view[0][0]);
        renderer->m_shader->setMat4("model", 1, GL_FALSE, &transform->getModelMatrix()[0][0]);

        renderer->m_model->draw(*renderer->m_shader, m_whiteTextureId); 
    }
}