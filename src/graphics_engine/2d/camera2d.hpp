#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;
//-----------------------------------------------------------------------CAMERA 2D----------------------------------------------------------
class Camera2D{
    public:
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 up;
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 rot;
    float fov = 45.0f;
    int width = 800;
    int height = 600;
    float near = 0.1f;
    float far = 100.0f;
    //constructor
    Camera2D();
    
    ~Camera2D();
    
    void updateCamera();
    



    void setUniforms(unsigned int shaderProgram);
   
};






