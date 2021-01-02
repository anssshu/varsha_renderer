#pragma once



#include "camera.hpp"
#include "model.hpp"
#include "light.hpp"

//scene to be made independent of the renderer
//scene object gives scene_data to the renderer

//renderer creates model_arrays,light_array and camera and connect it then stores the scene with the pointer

//a basic ascene contains an array of models and a camera and a light

//a scene is a container for models camera and light

class Scene{
public:
    unsigned int ID;
    //scene datastructure to store scene loaded from a file
    SceneData scene_data;//for loading and saving scene files

    Camera camera;
    vector<Light*> light_array;
    vector<Model*> model_array;

    //constructor

    //destructor

    //other functions
    void addModel(Model* pModel );


    void addLight(Light* pLight);




};






