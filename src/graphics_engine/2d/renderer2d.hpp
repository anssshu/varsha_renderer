//

//                                      2D RENDERER INTERFACE
//



#pragma once
#include "scene2d.hpp"
//IRenderer
class Renderer2D{
    public:
    Scene2D* current_scene;
    //list of all the virtual function for the renderer
    //create a single mesh(VAO indice_size) from mesh_data
    //virtual Mesh processMeshData(MeshData mesh_data) = 0;

    //process model data and create an array of meshes(VAO,indices)
    //virtual vector<Mesh> processModelData(ModelData data)=0;

    //function to render a single Model
    //virtual void renderMesh(Mesh mesh,Shader* shader)=0;

    //process models with model_data and stores them to model array
    //virtual void loadModel(Model* model)=0;
    //function to render a Model 
    //virtual void renderModel()=0;
    //load scene 
    virtual void loadScene2D(Scene2D* scene)=0;
    //function to render the current scene
    virtual void renderScene2D()=0;
};