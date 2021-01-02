#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;


//every 3d object inherits from the base object
class BaseObject
{
public:
unsigned int ID;
vec3 pos = vec3(0.0);
vec3 rot = vec3(0.0);
vec3 scale = vec3(1.0);
mat4 model = mat4(1.0);
mat4 view = mat4(1.0);
mat4 projection = mat4(1.0);


virtual void init() = 0;

virtual void update() = 0;

virtual void draw() = 0 ;


};



