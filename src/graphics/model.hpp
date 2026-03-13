#pragma once
#include "mesh.hpp"
#include <vector>
#include <string>

class Model 
{
public:
    Model(const std::string& path);
    void draw(Shader& shader, unsigned int whiteTextureID);

private:
    std::vector<Mesh> m_meshes;
    std::vector<Texture> m_loadedTextures;

    void loadModel(const std::string& path);
};