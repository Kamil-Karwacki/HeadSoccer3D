#include <glad/glad.h>
#include "model.hpp"
#include "tiny_obj_loader.h"
#include "stb_image.h"
#include <iostream>
#include <unordered_map>

Model::Model(const std::string& path)
{
    loadModel(path);
}

Model::Model(Mesh mesh)
{
    m_meshes.push_back(mesh);
}

void Model::draw(Shader& shader, unsigned int whiteTextureID)
{
    for(unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].draw(shader, whiteTextureID);
}

void Model::loadModel(const std::string& path)
{
    std::cout << "Loading model from: " << path << "\n";
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config)) 
    {
        if (!reader.Error().empty()) std::cerr << "TinyObjReader: " << reader.Error();
        exit(1);
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    size_t numMaterials = materials.empty() ? 1 : materials.size();
    
    struct MeshData 
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        std::unordered_map<Vertex, uint32_t> uniqueVertices;
    };
    std::vector<MeshData> meshDataList(numMaterials + 1);

    for (size_t s = 0; s < shapes.size(); s++) 
    {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            
            int mat_id = shapes[s].mesh.material_ids[f];
            if (mat_id < 0) mat_id = numMaterials;

            glm::vec3 face_color = glm::vec3(1.0f);
            if (mat_id >= 0 && mat_id < materials.size()) 
            {
                face_color = glm::vec3(
                    materials[mat_id].diffuse[0], 
                    materials[mat_id].diffuse[1], 
                    materials[mat_id].diffuse[2]);
            }

            for (size_t v = 0; v < fv; v++)
            {
                Vertex vertex{};
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                vertex.position = glm::vec3(
                    attrib.vertices[3*idx.vertex_index+0], 
                    attrib.vertices[3*idx.vertex_index+1], 
                    attrib.vertices[3*idx.vertex_index+2]);
                
                if (idx.normal_index >= 0) vertex.normal = glm::vec3(
                    attrib.normals[3*idx.normal_index+0], 
                    attrib.normals[3*idx.normal_index+1], 
                    attrib.normals[3*idx.normal_index+2]);

                if (idx.texcoord_index >= 0) vertex.texCoords = glm::vec2(
                    attrib.texcoords[2*idx.texcoord_index+0], 
                    attrib.texcoords[2*idx.texcoord_index+1]);
                
                glm::vec3 vertex_color = glm::vec3(1.0f);
                if (attrib.colors.size() > 0) vertex_color = glm::vec3(
                    attrib.colors[3*idx.vertex_index+0], 
                    attrib.colors[3*idx.vertex_index+1], 
                    attrib.colors[3*idx.vertex_index+2]);

                vertex.color = face_color * vertex_color;

                auto& currentMesh = meshDataList[mat_id];
                if(currentMesh.uniqueVertices.count(vertex) == 0) 
                {
                    currentMesh.uniqueVertices[vertex] = static_cast<uint32_t>(currentMesh.vertices.size());
                    currentMesh.vertices.push_back(vertex);
                }
                currentMesh.indices.push_back(currentMesh.uniqueVertices[vertex]);
            }
            index_offset += fv;
        }
    }

    for (size_t i = 0; i < materials.size(); i++)
    {
        if (meshDataList[i].vertices.empty()) continue;

        std::string diffuse_path = materials[i].diffuse_texname;
        if (!diffuse_path.empty()) 
        {
            std::string fullPath = PROJECT_DIR "assets/textures/" + diffuse_path;
            std::cout << "Loading diffuse texture from: " << fullPath << "\n";

            Texture texture;
            texture.type = "texture_diffuse";
            glGenTextures(1, &texture.id);
            glBindTexture(GL_TEXTURE_2D, texture.id);

            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 4);
            
            if (data) 
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                meshDataList[i].textures.push_back(texture);
            }
            else
            {
                std::cerr << "Couldn't load texture: " << fullPath << "\n";
            }
            stbi_image_free(data);
        }

        m_meshes.push_back(Mesh(meshDataList[i].vertices, meshDataList[i].indices, meshDataList[i].textures));
    }

    if (!meshDataList[numMaterials].vertices.empty()) 
        m_meshes.push_back(Mesh(meshDataList[numMaterials].vertices, meshDataList[numMaterials].indices, {}));
}