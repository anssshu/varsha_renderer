#pragma once

#include "gl_renderer/gl_renderer.hpp"//----it consisit of  renderer 
//#include "vulkan_renderer"
//#include "gles_renderer"


//the world is a container of scenes 
//it has a scene array a renderer and an input processor
class World
{

public:
Renderer* renderer;
vector<Scene*> scene_array;

//constructor

World();


void loadScene(unsigned int SceneID,RENDER_SETTING setting);


void reset();


void update();

void addScene(Scene* scene);



//draw the current scene 
void draw();


    

   
};



