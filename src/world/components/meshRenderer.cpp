#include <glad/glad.h>
#include "meshRenderer.hpp"
#include "graphics/shader.hpp"
#include "core/application.hpp"

void MeshRenderer::start()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    
    if (transform == nullptr)
        std::cerr << "Error: MeshRenderer requires transform component!\n";

    if (m_mesh == nullptr)
        std::cerr << "Error: MeshRenderer requiers model!\n";
}

void MeshRenderer::draw()
{
    Transform* transform = m_entity->GetComponent<Transform>();
    if (!m_mesh || !transform)
        return;

    Application& app = Application::Get();    
    std::shared_ptr<Shader> shader = app.getShader("default");
    glm::mat4 model = transform->getModelMatrix();

    shader.get()->use();
    shader->setMat4("model", 1, GL_FALSE, &model[0][0]);

    m_mesh->draw(*shader.get(), app.getWhiteTexture());
}