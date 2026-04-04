#include <glad/glad.h>
#include "mesh.hpp"
#include <iostream>
#include <stdexcept>
#include "tiny_obj_loader.h"
#include "stb_image.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader, unsigned int whiteTextureID) 
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    bool hasDiffuseTexture = false;

    for (unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); 

        std::string number;
        std::string name = m_textures[i].type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
            hasDiffuseTexture = true;
        }
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt((name + number).c_str(), i);
        
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    if(!hasDiffuseTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, whiteTextureID);
        shader.setInt("texture_diffuse1", 0);
    }
    
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh Mesh::createBox(const glm::vec3& size, const glm::vec3& color)
{
    Mesh mesh;
    
    glm::vec3 half = size * 0.5f;
    float w = half.x;
    float h = half.y;
    float d = half.z;

    // 24 Vertices: Position, Normal, Texture Coordinate
    mesh.m_vertices = 
    {
        // Front face (+Z)
        {{-w, -h,  d}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}, color},
        {{ w, -h,  d}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}, color},
        {{ w,  h,  d}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}, color},
        {{-w,  h,  d}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}, color},

        // Back face (-Z)
        {{ w, -h, -d}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, color},
        {{-w, -h, -d}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}, color},
        {{-w,  h, -d}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}, color},
        {{ w,  h, -d}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}, color},

        // Left face (-X)
        {{-w, -h, -d}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, color},
        {{-w, -h,  d}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}, color},
        {{-w,  h,  d}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}, color},
        {{-w,  h, -d}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}, color},

        // Right face (+X)
        {{ w, -h,  d}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, color},
        {{ w, -h, -d}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}, color},
        {{ w,  h, -d}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}, color},
        {{ w,  h,  d}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}, color},

        // Top face (+Y)
        {{-w,  h,  d}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, color},
        {{ w,  h,  d}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}, color},
        {{ w,  h, -d}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}, color},
        {{-w,  h, -d}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}, color},

        // Bottom face (-Y)
        {{-w, -h, -d}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, color},
        {{ w, -h, -d}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}, color},
        {{ w, -h,  d}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}, color},
        {{-w, -h,  d}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}, color}
    };

    mesh.m_indices = 
    {
         0,  1,  2,  2,  3,  0, // Front
         4,  5,  6,  6,  7,  4, // Back
         8,  9, 10, 10, 11,  8, // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20  // Bottom
    };

    mesh.setupMesh();
    return mesh;
}