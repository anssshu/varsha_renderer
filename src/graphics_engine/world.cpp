#include "world.hpp"


World::World(){
    //create model

    //create a scene

    //load the scene to the world
}

void World::loadScene(unsigned int SceneID,RENDER_SETTING setting){
    //construct a render which is of opengl TYPE

    //create an opengl renderer
    if (setting == OPENGL){
        renderer = new GLRenderer();//OPENGL RENDER 
    }
    

    renderer->loadScene(scene_array[SceneID]);
}

void World::reset(){

}

void World::update(){
    //update the model and view matrix of the camera
    renderer->current_scene->camera.updateCamera();
    //update all the models
    for(int i=0;i<renderer->current_scene->model_array.size();i++)
    {
        renderer->current_scene->model_array[i]->update();
    }
}
void World::addScene(Scene* scene){  
    scene->ID = scene_array.size();
    scene_array.push_back(scene);
}


//draw the current scene 
void World::draw(){
renderer->renderScene();
}