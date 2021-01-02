#pragma once
//#include "scene.hpp"
#include "renderer2d.hpp" //renderer interface
#include "../renderer_gl/shader_gl.hpp"

class GLRenderer2D:public Renderer2D
{   
    public:
    float rot = 0.0f;
    //container for the scene
    //Scene* current_scene;----interface has a current scene
 

    //container for Models;
    vector<Model2D*> model_array;
    

    //default camera
    //Camera2D* camera;

    //default light
    //Light2D light;

    //constructor
    GLRenderer2D();

    //destructor
    ~GLRenderer2D();
    //create a single mesh(VAO indice_size) from mesh_data
    //Mesh processMeshData(MeshData mesh_data);

    //process model data and create an array of meshes(VAO,indices)
    //vector<Mesh> processModelData(ModelData data);

    //function to render a single Model
    //void renderMesh(Mesh mesh,Shader* shader);

    //process models with model_data and stores them to model array
    //void loadModel(Model2D* model);
    //function to render a Model 
    //void renderModel();
    //load scene 
    void loadScene2D(Scene2D* scene);
    //function to render the current scene
    void renderScene2D();



};