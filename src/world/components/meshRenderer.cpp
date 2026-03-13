#include <glad/glad.h>
#include "meshRenderer.hpp"
#include "graphics/shader.hpp"
#include "core/application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void MeshRenderer::start()
{
    m_transform = entity->GetComponent<Transform>();
    
    if (m_transform == nullptr)
    {
        std::cerr << "Warning: MeshRenderer requires transform component!\n";
    }
}

void MeshRenderer::draw()
{
    if(!m_mesh || !m_transform)
        return;

    Application& app = Application::Get();    
    std::shared_ptr<Shader> shader = app.getShader("default");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_transform->m_position);

    model = glm::rotate(model, glm::radians(m_transform->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_transform->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_transform->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, m_transform->m_scale);
    shader.get()->use();
    shader->setMat4("model", 1, GL_FALSE, &model[0][0]);

    m_mesh->draw(*shader.get(), app.getWhiteTexture());
}