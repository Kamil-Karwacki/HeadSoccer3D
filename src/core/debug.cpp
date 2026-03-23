#include "debug.hpp"
#include <glad/glad.h>

std::vector<Debug::DebugVertex> Debug::m_vertices;
std::vector<Debug::DebugLine> Debug::m_lines;
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, m_color));

    glBindVertexArray(0);
}

void Debug::addLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color, float duration)
{
    m_lines.push_back({from, to, color, duration});
}

void Debug::render(Shader& shader)
{
    if (m_lines.empty()) return;

    m_vertices.clear();
    for (const auto& line : m_lines)
    {
        m_vertices.push_back({line.m_start, line.m_color});
        m_vertices.push_back({line.m_end, line.m_color});
    }

    shader.use();
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(DebugVertex), m_vertices.data(), GL_DYNAMIC_DRAW);
    
    glDrawArrays(GL_LINES, 0, m_vertices.size());
    glBindVertexArray(0);
}

void Debug::update(float deltaTime)
{
    for (auto& line : m_lines)
    {
        line.m_timeRemaining -= deltaTime;
    }

    m_lines.erase(
        std::remove_if(m_lines.begin(), m_lines.end(),
            [](const DebugLine& line) { return line.m_timeRemaining <= 0.0f; }),
        m_lines.end()
    );
}
