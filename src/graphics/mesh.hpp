#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vector>
#include <string>
#include "shader.hpp"
#include <functional>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color;

    bool operator==(const Vertex& other) const
    {
        return position == other.position && normal == other.normal && texCoords == other.texCoords;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            size_t seed = 0;
            auto hash_combine = [](size_t& seed, size_t hash_val) {
                seed ^= hash_val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            };

            hash_combine(seed, std::hash<glm::vec3>()(vertex.position));
            hash_combine(seed, std::hash<glm::vec3>()(vertex.normal));
            hash_combine(seed, std::hash<glm::vec2>()(vertex.texCoords));
            hash_combine(seed, std::hash<glm::vec3>()(vertex.color));

            return seed;
        }
    };
}

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh
{
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    void draw(Shader& shader, unsigned int whiteTextureID);
private:
    unsigned int m_VAO, m_VBO, m_EBO;
    void setupMesh();
};