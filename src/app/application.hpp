
#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "graphics_engine/2d/engine.hpp"
#include "graphics_engine/3d/engine.hpp"
#include "app/suzane.hpp"

class Application
{
    private:
    unsigned int display_setting,render_mode,renderer_setting;
    public:
    Display* display;

    Application();
    ~Application();
    //void addWorld(World* world);
     void run();
     void initDisplay(const int WIDTH,const int HEIGHT,const char* TITLE);

};

#endif
