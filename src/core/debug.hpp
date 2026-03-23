#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "graphics/shader.hpp"

class Debug
{
public:
    static void init();
    static void addLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color = glm::vec3(0.0f, 1.0f, 0.0f));
    static void render(Shader& shader);

private:
    struct DebugVertex 
    {
        glm::vec3 position;
        glm::vec3 color;
    };

    static std::vector<DebugVertex> m_vertices;
    static unsigned int m_VAO;
    static unsigned int m_VBO;
};