#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

struct Vertex2D {
    // position
    glm::vec3 Position;
    // normal  
    glm::vec2 TexCoords;
    
};

struct Mesh2DData{
    vector<Vertex2D> vertices;
    vector<unsigned int> indices;
};

struct Mesh2D{
    unsigned int VAO;
    unsigned int indices_size;
};

struct Texture2DData{
    unsigned int ID;
    string path;
    string name;
};

struct Transform2DData{
    vec3 pos = vec3(0.0f,0.0f,0.0f);
    vec3 rot = vec3(0.0f,0.0f,0.0f);
    vec3 scale = vec3(1.0f,1.0f,1.0f);
};

struct Shader2DData{
    const char* vs_path;
    const char* fs_path;
};

struct MatrialData2D{

};


