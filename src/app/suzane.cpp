#include "suzane.hpp"
Suzane::Suzane():Model("models/suzane/suzane.obj")
    {
         rot.x =  -30.0f;
    }

void Suzane::update(){
    
    rot.y+=1.0f;
}
