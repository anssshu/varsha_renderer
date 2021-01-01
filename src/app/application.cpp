

#include "application.hpp"

Application::Application(){

    // if glfw is choosen then GlFW window will be choosen
    

    //create a glfw window
    initDisplay(800,600,"VARSHA RENDERER",GLFW);//THE CURRENT DISPLAY IS CREATED BY GLFW
    
    
    //create a world
    World* world = new World();//a container of scenes and a renderer

    //create a scene
    Scene* scene = new Scene();//a container of lights and models and a camera

    //create a model
    Model* suzane = new Suzane();
    

    scene->addModel(suzane);
    world->addScene(scene);

    //load the scene with opengl renderer
    world->loadScene(0,OPENGL);//OPEN GL IS THE CURRENT RENDERER

    //connect the world to the display
    addWorld(world);


}

void Application::initDisplay(const int WIDTH,const int HEIGHT,const char* TITLE,DISPLAY_SETTING display_option)
{
    //code for creating a glfw window
    if (display_option == GLFW)
    {
        display = new GlfwDisplay();
        display->initWindow(WIDTH,HEIGHT,TITLE);
    }    
    

};
void Application::run()
{
    //run the display   display is having the main loop of the application
    display->run();
}
void Application::addWorld(World* world){
    display->addWorld(world);
}
Application::~Application()
{

}
