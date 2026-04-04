#include <glad/glad.h>
#include "meshRenderer.hpp"
#include "graphics/shader.hpp"
#include "core/application.hpp"

void MeshRenderer::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (!transform)
        std::cerr << "Error: MeshRenderer requires transform component!\n";

    if (!m_model)
        std::cerr << "Error: MeshRenderer requiers model!\n";
}

void MeshRenderer::draw()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    if (!m_model || !transform)
        return;

    Application& app = Application::Get();    
    std::shared_ptr<Shader> shader = app.getShader("default");
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(model, m_offset);
    model *= transform->getModelMatrix();
    shader->setMat4("model", 1, GL_FALSE, &model[0][0]);

    m_model->draw(*shader.get(), app.getWhiteTexture());
}