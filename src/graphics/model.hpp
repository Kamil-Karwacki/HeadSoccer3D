#pragma once
#include "mesh.hpp"
#include <vector>
#include <string>

class Model 
{
public:
    Model(const std::string& path);
    Model(Mesh mesh);
    void draw(Shader& shader, unsigned int whiteTextureID);

private:
    std::vector<Mesh> m_meshes;
    void loadModel(const std::string& path);
};