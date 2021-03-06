#pragma once
//#include "scene.hpp"
#include "../../renderer_interface_3d.hpp" //renderer interface
#include "shader_gl.hpp"

class GLRenderer3D:public IRenderer3D
{   
    public:
    float rot = 0.0f;
    //container for the scene
    //Scene* current_scene;----interface has a current scene
 

    //container for Models;
    vector<Model*> model_array;
    

    //default camera
    //Camera2D* camera;

    //default light
    Light light;

    //constructor
    GLRenderer3D();

    //destructor
    ~GLRenderer3D();
    //create a single mesh(VAO indice_size) from mesh_data
    Mesh processMeshData(MeshData mesh_data);

    //process model data and create an array of meshes(VAO,indices)
    vector<Mesh> processModelData(ModelData data);

    //function to render a single Model
    void renderMesh(Mesh mesh,Shader* shader);

    //process models with model_data and stores them to model array
    void loadModel(Model* model);
    //function to render a Model 
    void renderModel();
    //load scene 
    void loadScene(unsigned int ID);
    //function to render the current scene
    void renderScene();

    void addScene(Scene* scene);
    void update();
    void reset();



};
