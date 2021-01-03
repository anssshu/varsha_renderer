
//Display interface to connect to the differernt kinds of display ex-glfw,SDL etc



/*
            INTERFACE TO THE DISPLAY ----------glfw interface in this case ------------
            my display interface has 2 renderers and it switches between them

*/
#pragma once
#include "../3d/engine.hpp"
#include "../2d/engine.hpp"
class Display{
    public:
        //World* world;
        unsigned int render_mode;

        IRenderer3D* renderer_3d;
        IRenderer2D* renderer_2d;
        
        //Display() ;
        //GLFWwindow* window;
        //Display(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE);
        //virtual ~Display() = default;

        //
        virtual void initWindow(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE)=0;

        //function for running of the loop
        virtual void run() = 0;

        void renderScene(){

            if (render_mode == MODE_3D)
                {
                    renderer_3d->renderScene();
                }
            //render the 2d world    
            else
                {
                    renderer_2d->renderScene();
                }
        };

        //process input

        //virtual void addWorld(World* world) = 0;
};