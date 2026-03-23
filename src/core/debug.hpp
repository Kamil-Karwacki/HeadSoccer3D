#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "graphics/shader.hpp"

class Debug
{
public:
    static void init();
    static void addLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f), float duration = 0.0f);
    static void render(Shader& shader);
    static void update(float deltaTime);

private:
    struct DebugVertex 
    {
        glm::vec3 m_position;
        glm::vec3 m_color;
    };

    struct DebugLine
    {
        glm::vec3 m_start;
        glm::vec3 m_end;
        glm::vec3 m_color;
        float m_timeRemaining;
    };

    static std::vector<DebugLine> m_lines;
    static std::vector<DebugVertex> m_vertices;
    static unsigned int m_VAO;
    static unsigned int m_VBO;
};