#pragma once

#include "graphics_engine/3d/engine.hpp"
#include "suzane.hpp"
class MainScene:public Scene 
{
    public:
        MainScene(){
            //create the main scene
            Suzane* suzane = new Suzane();
            addModel(suzane);
        }
};