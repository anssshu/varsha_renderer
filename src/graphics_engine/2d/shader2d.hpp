//ISHADER
#pragma once
#include "structures2d.hpp"
#include "helpers2d.hpp"



//shader class
class Shader2d{
    public:
    unsigned int textureCount , indices_size;
    unsigned int VAO;
    int shaderProgram;
    vector<Texture2DData> textures;
    //load shaderfiles and create the shaderProgram
   
    //Shader(ShaderData data);
    //Shader(string vertex_shader_path,string fragment_shader_path);
    //~Shader();
    virtual void loadVertexData(Mesh2D mesh)=0;
    virtual void renderContainer()=0;
    virtual void render()=0;
    //for rgb falg ==0 ,for rgba flag =1
    virtual void setModelViewProjection(mat4 model=mat4(1.0),mat4 view = mat4(1.0),mat4 projection = mat4(1.0))=0;

    virtual void connectUniformTexturetoTextureSlot(string path,const string name)=0;
    //load a single texture file
    virtual void loadTextureData(Texture2DData tex)=0;
    //load multiple texture files
    virtual void loadTextureList(vector<Texture2DData> texture_list)=0;
    // draw the textures
    virtual void bindTextures()=0;
    
    //FOR OPENGL SHADER ONLY
    
    
    virtual void use()=0;

    

    virtual void setUniformBool(const std::string &name, bool value) const=0;
    
    // ------------------------------------------------------------------------
    virtual void setUniformInt(const std::string &name, int value) const=0;
   
    // ------------------------------------------------------------------------
    virtual void setUniformFloat(const std::string &name, float value) const=0;
   
    // ------------------------------------------------------------------------
    virtual void setUniformVec2(const std::string &name, const glm::vec2 &value) const=0;
    
    virtual void setUniformVec2(const std::string &name, float x, float y) const=0;
    
    // ------------------------------------------------------------------------
    virtual void setUniformVec3(const std::string &name, const glm::vec3 &value) const=0;
   
    virtual void setUniformVec3(const std::string &name, float x, float y, float z) const=0;
   
    // ------------------------------------------------------------------------
    virtual void setUniformVec4(const std::string &name, const glm::vec4 &value) const=0;
   
    virtual void setUniformVec4(const std::string &name, float x, float y, float z, float w)=0 ;
    
    // ------------------------------------------------------------------------
    virtual void setUniformMat2(const std::string &name, const glm::mat2 &mat) const =0;
  
    // ------------------------------------------------------------------------
    virtual void setUniformMat3(const std::string &name, const glm::mat3 &mat) const =0;
   
    // ------------------------------------------------------------------------
    virtual void setUniformMat4(const std::string &name, const glm::mat4 &mat) const =0;
    

     
};