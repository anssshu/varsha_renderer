#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

using namespace std;
using namespace glm;

struct Vertex2D {
    // position
    glm::vec3 Position;
    // normal  
    glm::vec2 TexCoords;
    
};

struct Mesh2DData{
    vector<Vertex2D> vertices;
    vector<unsigned int> indices;
};

struct Mesh2D{
    unsigned int VAO;
    unsigned int indices_size;
};

struct Texture2DData{
    unsigned int ID;
    string path;
    string name;
};

struct Transform2DData{
    vec3 pos = vec3(0.0f,0.0f,0.0f);
    vec3 rot = vec3(0.0f,0.0f,0.0f);
    vec3 scale = vec3(1.0f,1.0f,1.0f);
};

struct Shader2DData{
    const char* vs_path;
    const char* fs_path;
};

struct MatrialData2D{

};
std::string readFile(const char* filePath);
Mesh2D createMesh2D(Mesh2DData mesh2d_data);
unsigned int createShaderProgram(string vertex_shader_path,string fragment_shader_path);
unsigned int loadTexture2D(const char* filePath);
void frameBufferSize_callback(GLFWwindow*,int width,int height);
void processInput(GLFWwindow* window);



int main(){
    //initialise glfw
    glfwInit();

    //opengl version 3.3
    //specify opengl major version -- 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    //specify opengl minor version--- 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //specify opengl profile --core profile 
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); for apple computers

    //create a window
    GLFWwindow* window = glfwCreateWindow(800,600,"WINDOW",nullptr,nullptr);

    //if window creation fails
    if (window == NULL)
    {
        glfwTerminate();
        std::cout << "window creation failed" <<std::endl;
        return -1;
    }

    //make context of the window to that of the current thread--so opengl context is connected to the current thread
    glfwMakeContextCurrent(window);
    //set framebuffer resize opeation
    glfwSetFramebufferSizeCallback(window,frameBufferSize_callback);

    //load the openGL function pointer to glad
    //if load fails
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "glad initialisation failed" <<std::endl;
        return -1;
    }

    //render loop
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        //render opengl data

        //fill the color buffer with color
        glClearColor(0.2f,0.2f,0.1f,1.0f);
        //clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        //check for mouse movements or keyboard input
        glfwPollEvents();
        //swapbuffer
        glfwSwapBuffers(window);
        
    }

    //terminate glfw
    glfwTerminate();
    //tell opengl the size of the rendering window
    //opengl renderring window
    
    std::cout << "main function was running\n" ;
    return 1;
}

void frameBufferSize_callback(GLFWwindow*,int width,int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout<< "A key was pressed"   <<std::endl;
    }
}






















std::string readFile(const char* filePath)
    {
        
        

        std::ifstream file;
        std::string fileString;
        
        //const char* fileChar;
        
        // ensure ifstream objects can throw exceptions:
        file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      
        try 
        {
            // open files
            file.open(filePath);
            
            std::stringstream vShaderStream; 
            // read file's buffer contents into streams
            vShaderStream << file.rdbuf();
            		
            // close file handlers
            file.close();
            
            // convert stream into string
            fileString = vShaderStream.str();
            		
            
        }

        catch (std::ifstream::failure& e)
        {
            std::cout << "unable to raed file:" << filePath << std::endl;
        }

        //fileChar = fileString.c_str();

        return fileString;

}

Mesh2D createMesh2D(Mesh2DData vertex_data)
{
    Mesh2D mesh;
    unsigned int VAO,EBO,VBO;

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    //create VBO
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.vertices.size()*sizeof(float), &vertex_data.vertices[0], GL_STATIC_DRAW);

    //create EBO
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,vertex_data.indices.size()*sizeof(unsigned ),&vertex_data.indices[0],GL_STATIC_DRAW);

    

    //create attribute pointers

  

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)0);
    
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D,TexCoords));

    
    
    //unbing buffer
    glBindBuffer(GL_ARRAY_BUFFER,0);
    //unbind Vertex Array
    glBindVertexArray(0);

    mesh.VAO = VAO;
    mesh.indices_size = vertex_data.indices.size();

    return mesh;
}

unsigned int createShaderProgram(string vertex_shader_path,string fragment_shader_path){
        string _vs_code = readFile(vertex_shader_path.c_str());
        string _fs_code = readFile(fragment_shader_path.c_str());

        const char* vscode = _vs_code.c_str();
        const char* fscode = _fs_code.c_str();

        //create vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader,1,&vscode,NULL);
        glCompileShader(vertexShader);//compile shader code

        //check for error
         int success;
        char infolog[512];
        glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader,512,NULL,infolog);
            cout<<"vertex shader compilation failed:"<<infolog<<endl;
        }

        //create fragmentShader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        //copy shader code
        glShaderSource(fragmentShader,1,&fscode,NULL);
        //compile shader
        glCompileShader(fragmentShader);

        //check for errors
       

        glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader,512,NULL,infolog);
            cout<<"fragment shader compilation failed:"<<infolog<<endl;
        }



        //link all the shaders
        unsigned int shaderProgram = glCreateProgram();
        //attach vertext shaed
        glAttachShader(shaderProgram,vertexShader);
        //attach fragment shader
        glAttachShader(shaderProgram,fragmentShader);
        //link shader program
        glLinkProgram(shaderProgram);

        //check for error
        glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram,512,NULL,infolog);
            cout<<" shaderProgram linking  failed:"<<infolog<<endl;
        }


        //delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;

};

unsigned int loadTexture2D(const char* filePath){
    // ---------
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* data;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data)
    {   
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
        format = GL_RGBA; 
       
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
};