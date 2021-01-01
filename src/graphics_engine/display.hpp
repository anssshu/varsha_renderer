
//Display interface to connect to the differernt kinds of display ex-glfw,SDL etc



/*
            INTERFACE TO THE DISPLAY ----------glfw interface in this case ------------

*/
#pragma once
#include "world.hpp"
class Display{
    public:
        //World* world;

        //Display() ;
       //GLFWwindow* window;
        //Display(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE);
        //virtual ~Display() = default;

        //
        virtual void initWindow(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE)=0;

        //function for running of the loop
        virtual void run() = 0;

        virtual void addWorld(World* world) = 0;
};