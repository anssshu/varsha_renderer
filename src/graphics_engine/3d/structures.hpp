
/*
This file defines all the data structures
used in the application
*/

#pragma once


//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>



#include <iostream>
#include <string>
#include <vector>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

//setting for the renderer;
enum DISPLAY_SETTING{
    GLFW,
    SDL
};
//choose a rendring mode
enum RENDER_MODE{
    MODE_3D,
    MODE_2D
};
//choise for rendring framework
enum RENDER_SETTING {
        OPENGL,
        OPENGLES,
        VULKAN,
        DIRECTX
    };

struct VertexData{
    //vertices
    vector<float> vertices = {
     //pos                  //uv cord   
     0.5f,  0.5f, 0.0f,     1.0f,1.0f,// top right
     0.5f, -0.5f, 0.0f,     1.0f,0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,     .0f,0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,     0.0f,1.0f// top left 
    };
    //indices
    vector<unsigned int> indices={  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };
};

struct Mesh{
    unsigned int VAO;
    unsigned int indices_size;
};
struct TextureData{
    unsigned int ID;
    //const char* path;
    //const char* name;
    string path;
    string name;
};

struct TransformData{
    vec3 pos = vec3(0.0f,0.0f,0.0f);
    vec3 rot = vec3(0.0f,0.0f,0.0f);
    vec3 scale = vec3(1.0f,1.0f,1.0f);
};

struct ShaderData{
    const char* vs_path;
    const char* fs_path;
};

struct MatrialData{

};

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};
/*
struct VertexData {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};
*/
//for retrive data with assimp
struct Texture {
    unsigned int id;
    string type;
    string path;
};
/*
struct TextureData {
    unsigned int id;
    string type;
    string path;
};
*/
struct MeshData
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<TextureData> textures;
};

//for loading and saving to file
struct ModelData
{
    vector<MeshData> mesh_data_array;
    vector<TextureData> loaded_textures;
    string path;
};


struct CameraData
{

};

struct LightData
{

};
//for loading and saving to file
struct SceneData
{
    vector<ModelData> model_data_array;
    vector<LightData> light_data_array;
    CameraData camera_data;
    string path;
};


