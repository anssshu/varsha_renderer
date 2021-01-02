/*
INTERFACE TO MULTIPLE RENDERER -- gl,gles and vulkan
*/

#pragma once

//#include "../common/renderer_i.hpp"
#include "scene.hpp"
//IRenderer
class IRenderer3D{
    public:
    vector<Scene*> scene_array;
    Scene* current_scene;
    //list of all the virtual function for the renderer
    //create a single mesh(VAO indice_size) from mesh_data
    virtual Mesh processMeshData(MeshData mesh_data) = 0;

    //process model data and create an array of meshes(VAO,indices)
    virtual vector<Mesh> processModelData(ModelData data)=0;

    //function to render a single Model
    virtual void renderMesh(Mesh mesh,Shader* shader)=0;

    //process models with model_data and stores them to model array
    virtual void loadModel(Model* model)=0;
    //function to render a Model 
    virtual void renderModel()=0;
    //add a scene to the scene array
    virtual void addScene(Scene* scene)=0;
    //load scene 
    //transfer graphics data and texture to memory or graphics card
    virtual void loadScene(unsigned int ID)=0;//cpnvert it into renderable format
    //function to render the current scene
    virtual void renderScene()=0;
    virtual void update()=0;//update all the models of the scene
    virtual void reset()=0;
};