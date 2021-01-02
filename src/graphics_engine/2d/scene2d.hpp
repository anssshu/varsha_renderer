#pragma once

#include "camera2d.hpp"
#include "model2d.hpp"
#include "light2d.hpp"

//scene to be made independent of the renderer
//scene object gives scene_data to the renderer

//renderer creates model_arrays,light_array and camera and connect it then stores the scene with the pointer

//a basic ascene contains an array of models and a camera and a light

//a scene is a container for models camera and light
class Scene2D{
public:
    unsigned int ID;
    //scene datastructure to store scene loaded from a file
    //SceneData scene_data;//for loading and saving scene files

    Camera2D camera;
    vector<Light2D*> light2d_array;
    vector<Model2D*> model2d_array;

    //constructor

    //destructor

    //other functions
    void addModel(Model2D* pModel );


    void addLight(Light2D* pLight);




};






