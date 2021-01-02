#pragma once

//#include "../2d/world2d.hpp"
#include "../display.hpp"

//-----------------------------------------------------------GlfDisplay CLASS------------------------------------------------------------------
class GlfwDisplay:public Display{

    public:
        //Renderer* renderer ;
        //World2D* world2d;
        //double yscroll;
        //static double mousex;
        //static double mousey;
        
        GLFWwindow* window;
        //GlfwDisplay();
        //GlfwDisplay(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE);
       
        ~GlfwDisplay();
       
        //void addWorld(World* w) ;
        void processInput(GLFWwindow* window);


        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


        void initWindow(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE);
        void run();
        //void render2D();
        //void render3D();
        void renderScene();

};

