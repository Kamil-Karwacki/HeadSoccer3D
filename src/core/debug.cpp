#include "debug.hpp"
#include <glad/glad.h>

std::vector<Debug::DebugVertex> Debug::m_vertices;
unsigned int Debug::m_VAO = 0;
unsigned int Debug::m_VBO = 0;

void Debug::init()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

    glBindVertexArray(0);
}

void Debug::addLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color)
{
    m_vertices.push_back({from, color});
    m_vertices.push_back({to, color});
}

void Debug::render(Shader& shader)
{
    if (m_vertices.empty()) return;

    shader.use();

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(DebugVertex), m_vertices.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_LINES, 0, m_vertices.size());

    glBindVertexArray(0);

    m_vertices.clear();
}