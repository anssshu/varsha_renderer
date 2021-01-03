#pragma once
#include "renderer2d.hpp"
#include "structures2d.hpp"
#include "helpers2d_gl.hpp"
#include "shader2d.hpp"
#include "shader2d_gl.hpp"

class GLRenderer2D:public IRenderer2D
{
    public:
    Mesh2D mesh;
    Shader2d* pshader;
    unsigned int shaderProgram,textureID;
    //construct the renderer
    GLRenderer2D(){

        Vertex2D v1,v2,v3,v4;
        v1.Position = vec3(-0.5, 0.5,0.0); //top left
        v2.Position = vec3( 0.5, 0.5,0.0); //top right
        v3.Position = vec3( 0.5,-0.5,0.0); //bottom right
        v4.Position = vec3(-0.5,-0.5,0.0); //bottom left

        v1.TexCoords = vec2(0.0,1.0); //top left
        v2.TexCoords = vec2(1.0,1.0); //top right
        v3.TexCoords = vec2(1.0,0.0); //bottom right
        v4.TexCoords = vec2(0.0,0.0); //bottom left

        //get mesh data
        Mesh2DData mesh2d_data ;
        mesh2d_data.vertices={v1,v2,v3,v4};
        mesh2d_data.indices = {0,1,2,2,0,3}; 
        
        //create VAO ,indices
        mesh = createMesh2D(mesh2d_data);

        pshader = new GLShader2D("shaders/sprite.vs","shaders/sprite.fs");
        
        //create a shader
        //shaderProgram = createShaderProgram("shaders/sprite.vs","shaders/sprite.fs");

        pshader->loadVertexData(mesh);
        pshader->loadTextureData({0,"textures/ubuntu.jpg","texture1"});
        //textureID = loadTexture2D("textures/ubuntu.jpg");

        //glUseProgram(shaderProgram);
       
        //glUniform1i(glGetUniformLocation(shaderProgram,"texture1"),textureID-1);
        //load textures

    };


   

    
    //this function will be called from the display to render the 2d scene
    void renderScene(){

       pshader->use();

       pshader->loadVertexData(mesh);

       pshader->bindTextures();

       pshader->renderContainer();


    };

    void addScene(){};
    void loadScene(){};
};