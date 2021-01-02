#include "camera.hpp"


///////////////////////////CAMERA 2D IMPLEMENTATION--------------------------------------------------------------
Camera::Camera()
{
    pos = vec3(0,0.0,3.0);
    up = vec3(0.0,1.0,0.0);
    target = vec3(0.0,0.0,0.0);
    model = glm::mat4(1.0);
    model = glm::translate(model,pos);
    model = glm::rotate(model,glm::radians(rot.x),glm::vec3(1.0,0.0,0.0));
    model = glm::rotate(model,glm::radians(rot.y),glm::vec3(0.0,1.0,0.0));
    model = glm::rotate(model,glm::radians(rot.z),glm::vec3(0.0,0.0,1.0));
    view = lookAt(pos,target,up);
    projection = glm::perspective(glm::radians(fov), (float)width /
(float)height, near, far);
}

Camera::~Camera()
{
    cout << "camera is dead" << endl;
}
void Camera::updateCamera()
{
    //target.x = pos.x;
    //target.y = pos.y;
    view = lookAt(pos,target,up);
    projection = glm::perspective(glm::radians(fov), (float)width /
(float)height, near, far);
}



void Camera::setUniforms(unsigned int shaderProgram)
{
    target.x = pos.x;
    target.y = pos.y;
    view = lookAt(pos,target,up);
    projection = glm::perspective(glm::radians(fov), (float)width /
(float)height, near, far);

    //shader.setUniformMat4("model",model);
    //send view and projection data to shader
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,&view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,&projection[0][0]);
    
}


