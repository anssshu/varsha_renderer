#include "model2d.hpp"


//--------------------------------------------MODEL IMPLEMENTATION----------------------------------------------------------------------------------


Model2D::Model2D(string const &path,const char* vertex_shader_path,const char* frag_shader_path)
{
    
    //load data to the model object
    
    //get the model data from the model
    data = loadModel(path);
    //data.path = path;//when added to scene scene stores the model path data

    //get the shader data 
    //shader_data.vs_path = vertex_shader_path;
    //shader_data.fs_path = frag_shader_path;

    //for creating mesh_arry connect to the renderer
    //shader = new Shader(vertex_shader_path,frag_shader_path);
    //load textures to the shader
    //shader->loadTextureList(data.loaded_textures);
    //cout<<"loaded--textures--count:::"<<data.loaded_textures.size()<<endl;
}
Model2D::~Model2D(){
    //delete shader;
    cout <<"model"<<ID<<" is dead"<<endl;
}

    
void Model2D::setPos(float x,float y,float z){
    pos.x =x ;
    pos.y = y;
    pos.z = z;
}

void Model2D::setRotZ(float angle_in_degree){
    rot.z = glm::radians(angle_in_degree);
}
void Model2D::setRotY(float angle_in_degree){
    rot.y = glm::radians(angle_in_degree);
}
void Model2D::setRotX(float angle_in_degree){
    rot.x = glm::radians(angle_in_degree);
}
void Model2D::setScale(float x,float y,float z){
    scale.x = x;
    scale.y = y;
    scale.z = z;
}
mat4 Model2D::updateModelMatrix(){
    model = mat4(1.0);
    model=translate(model,pos);
    model=rotate(model,radians(rot.x),vec3(1.0,0.0,0.0));
    model=rotate(model,radians(rot.y),vec3(0.0,1.0,0.0));
    model=rotate(model,radians(rot.z),vec3(0.0,0.0,1.0));
    model = glm::scale(model,scale);
    return model;
    //shader->setUniformMat4("model",model);
}
void Model2D::updateModelViewProjectionMatrix(Camera2D* cam){
    model = updateModelMatrix();
    shader->setUniformMat4("model",model);
    shader->setUniformMat4("view",cam->view);
    shader->setUniformMat4("projection",cam->projection);
}