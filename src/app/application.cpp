

#include "application.hpp"
#include "suzane_scene.hpp"
Application::Application(){

    //APPLICATION SETTINGS
    display_setting = GLFW;
    renderer_setting = OPENGL;
    render_mode = MODE_3D;




    
    //initialise the display and create the renderer
    
    initDisplay(800,600,"TITLE");

    
    

    //create a scene
    MainScene* scene = new MainScene();//a container of lights and models and a camera

    //create a model and add to scene
    //Model* suzane = new Suzane();
    //scene->addModel(suzane);


    
    
    display->renderer_3d->addScene(scene);
    //load the scene with opengl renderer
    display->renderer_3d->loadScene(0);//OPEN GL IS THE CURRENT RENDERER

    //connect the world to the display
    //addWorld(world);


}

void Application::initDisplay(const int WIDTH,const int HEIGHT,const char* TITLE)
{
    

    if (display_setting == GLFW)

    {
        display = new GlfwDisplay();
        display->initWindow(WIDTH,HEIGHT,TITLE);

        //set the display mode
        display->render_mode = render_mode;
    }

    //create a renderers for 2d and 3d mode
    //-----------------------3D MODE ------------------------------------------
    if (render_mode == MODE_3D)
    {
        //create a 3d renderer

        //choose a renderer from the input option
        if (this->renderer_setting ==OPENGL)
        {
            display->renderer_3d = new GLRenderer3D();
        }

        //-----------for vulkan and other renderers

    }
    //-----------------------2D MODE---------------------------------------
    else
    {
        //create a 2d renderer
        if (renderer_setting ==OPENGL)
        {
            //display->renderer_2d = new GLRenderer2D();
        }
    }
    
    

};
void Application::run()
{
    //run the display   display is having the main loop of the application
    display->run();
}

Application::~Application()
{

}
