
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "graphics_engine/engine.hpp"
#include "app/suzane.hpp"

class Application
{
    private:
    //World* world;
    //Scene* scene;
    //Model* suzane;
    public:
    Display* display;

    Application();
    ~Application();
    void addWorld(World* world);
     void run();
     void initDisplay(const int WIDTH,const int HEIGHT,const char* TITLE,DISPLAY_SETTING display_option);

};

#endif
