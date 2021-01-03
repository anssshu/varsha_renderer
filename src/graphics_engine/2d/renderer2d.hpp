#pragma once

//interface for the 2d renderer so that different renders (vulkan etc) can be used
class IRenderer2D
{
    public:
    //define all the virtual functions to be called from the RENDER2D implementations

    virtual void addScene()=0;
    virtual void loadScene()=0;

    
    //this function will be called from the display to render the 2d scene
    virtual void renderScene()=0;

};