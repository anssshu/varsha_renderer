#include "display_glfw.hpp"

//GlfwDisplay::GlfwDisplay(){}
void GlfwDisplay::initWindow(const unsigned int WIDTH,const unsigned int HEIGHT,const char* TITLE){

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }
    glfwMakeContextCurrent(window);

    //resize call back
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //cursor position call back
    glfwSetCursorPosCallback(window, mouse_callback);
    //mouse scroll  callback
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        //return -1;
    }

    


}

GlfwDisplay::~GlfwDisplay(){
    //triangle->~Triangle();
    glfwTerminate();
    std::cout << "GlfwDisplay is dead\n";

}

//void GlfwDisplay::addWorld(World* my_world){
   // world = my_world;
//}



void GlfwDisplay::run(){

    //initialise the world

    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //world->update();
        //world->draw();
        renderScene();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
void GlfwDisplay::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void GlfwDisplay::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //mousex = xpos;
    //mousey = ypos;

    //std::cout<<mousex<<":mousey:"<<mousey<<endl;
}

void GlfwDisplay::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  
   
   //yscroll = yoffset;
    
    
}


//-------------------INPUT-------------------------------
void GlfwDisplay::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    
    //      PROCESS 3D INPUT
    
    if (render_mode == MODE_3D)
    {
        Camera* camera;
        camera = &renderer_3d->current_scene->camera;

         camera->target.y = camera->pos.y;
        camera->target.x = camera->pos.x;
        camera->target.z = camera->pos.z-1.0f;
        //float deltaTime = 0.1;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->pos.z+=0.1f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->pos.z-=0.1f;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->pos.x+=0.1f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->pos.x-=0.1f;
    }
       

    
    
    
    
}



/*
void GlfwDisplay::renderScene(){
    if (render_mode == MODE_3D)
        {
            renderer_3d->renderScene();
        }
    else
        {
            renderer_2d->renderScene();
        }
}

*/