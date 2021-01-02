#pragma once
#include "structures.hpp"

#include "helpers.hpp"

#include "shader.hpp"
#include "camera.hpp"

//---------------------------------------------------------MODEL DEFINITION----------------------------------------------------------------------
class Model{
    public:
    unsigned int ID;
    Shader* shader;
    //Camera2D* camera;//connect it to the renderers camera   WHILE LOADING WITH RENDERER 
    ModelData data;//vertices indices texture array loaded from the 3d model
    ShaderData shader_data;
    vector<Mesh> mesh_array;//array of VAO and indices populated by the renderer
    vec3 pos = vec3(0.0);
    vec3 rot = vec3(0.0);
    vec3 scale = vec3(1.0);
    mat4 model = mat4(1.0);
    mat4 view = mat4(1.0);
    mat4 projection = mat4(1.0);
    Model(string const &path,const char* vertex_shader_path="shaders/model.vs",const char* frag_shader_path="shaders/model.fs");
    
    ~Model();
       
    void setPos(float x,float y,float z);
    
    void setRotZ(float angle_in_degree);
    void setRotY(float angle_in_degree);
    void setRotX(float angle_in_degree);
    void setScale(float x,float y,float z);
    mat4 updateModelMatrix();
    void updateModelViewProjectionMatrix(Camera* cam);
    virtual void update()=0;

    
};

