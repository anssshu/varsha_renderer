#pragma once
//#include "structures.hpp"
#include "helpers2d_gl.hpp"
#include "shader2d.hpp"

//shader class
class GLShader2D:public Shader2d{
    public:
    unsigned int textureCount , indices_size;
    unsigned int VAO;
    int shaderProgram;
    vector<Texture2DData> textures;
    //load shaderfiles and create the shaderProgram
   
    GLShader2D(Shader2DData data);
    GLShader2D(string vertex_shader_path,string fragment_shader_path);
    void loadVertexData(Mesh2D mesh);
    void renderContainer();
    void render();
    //for rgb falg ==0 ,for rgba flag =1
    void setModelViewProjection(mat4 model=mat4(1.0),mat4 view = mat4(1.0),mat4 projection = mat4(1.0));

    void connectUniformTexturetoTextureSlot(string path,const string name);
    //load a single texture file
    void loadTextureData(Texture2DData tex);
    //load multiple texture files
    void loadTextureList(vector<Texture2DData> texture_list);
    // draw the textures
    void bindTextures();
    void use();

    ~GLShader2D();

    void setUniformBool(const std::string &name, bool value) const;
    
    // ------------------------------------------------------------------------
    void setUniformInt(const std::string &name, int value) const;
   
    // ------------------------------------------------------------------------
    void setUniformFloat(const std::string &name, float value) const;
   
    // ------------------------------------------------------------------------
    void setUniformVec2(const std::string &name, const glm::vec2 &value) const;
    
    void setUniformVec2(const std::string &name, float x, float y) const;
    
    // ------------------------------------------------------------------------
    void setUniformVec3(const std::string &name, const glm::vec3 &value) const;
   
    void setUniformVec3(const std::string &name, float x, float y, float z) const;
   
    // ------------------------------------------------------------------------
    void setUniformVec4(const std::string &name, const glm::vec4 &value) const;
   
    void setUniformVec4(const std::string &name, float x, float y, float z, float w) ;
    
    // ------------------------------------------------------------------------
    void setUniformMat2(const std::string &name, const glm::mat2 &mat) const;
  
    // ------------------------------------------------------------------------
    void setUniformMat3(const std::string &name, const glm::mat3 &mat) const;
   
    // ------------------------------------------------------------------------
    void setUniformMat4(const std::string &name, const glm::mat4 &mat) const;
    

     
};

/*

Shader::Shader(ShaderData data){
    shaderProgram = loadShader(data.vs_path,data.fs_path);
}
Shader::Shader(string vertex_shader_path,string fragment_shader_path){
    

    shaderProgram = loadShader(vertex_shader_path,fragment_shader_path);

};
void Shader::loadVertexData(Mesh mesh){
    VAO = mesh.VAO;
    indices_size = mesh.indices_size;
}
void Shader::renderContainer(){

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
void Shader::render(){

use();
//bind textures
bindTextures();
//render container
renderContainer();
}
//for rgb falg ==0 ,for rgba flag =1
void Shader::setModelViewProjection(mat4 model,mat4 view ,mat4 projection)
{
    setUniformMat4("model",model);
    setUniformMat4("view",view);
    setUniformMat4("projection",projection);
}
//load a texture file and connect an opengl texture slot to the corresponding name in fragmen shader
void Shader::connectUniformTexturetoTextureSlot(string path,const string name){
    textureCount = loadTexture(path.c_str());
    //update texture data base
    //
    //update id with respect to
    textures.push_back({textureCount,path,name});
    use();
    setUniformInt(name,textures.size()-1);
    cout<<"shader.hpp:->loaded_texture-" <<" name:"<<name  <<" id:"<<textureCount<<" slot:"<<textures.size()-1<<" path:"<< path <<endl;
}
//load a single texture file
void Shader::loadTextureData(TextureData tex){
    connectUniformTexturetoTextureSlot(tex.path,tex.name);
}
//load multiple texture files
void Shader::loadTextureList(vector<TextureData> texture_list){
    for (int i=0;i<texture_list.size();i++)
    {
        //connectUniformTexturetoTextureSlot(texture_list[i].path,texture_list[i].name);
        loadTextureData(texture_list[i]);

    }

}
// draw the textures
void Shader::bindTextures(){
    //connect texture objects texture slots
    //activate a texture slot(GL_TEXTURE0 ,etc...) and connect the corresponding Texture Object with its ID
    for (unsigned int i =0;i<textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i].ID);
        //cout<<" total_sprites:"<<textures.size()<<" current_slot:"<< i <<" path:"<<textures[i].path<<" ID:"<<textures[i].ID<<endl;
    }
    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D,textures[0].ID);
}

void Shader::use(){
    glUseProgram(shaderProgram);
}

Shader::~Shader(){
    glDeleteProgram(shaderProgram);
    //cout<<"shader is deleted"<<endl;
}

void Shader::setUniformBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::setUniformInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setUniformFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setUniformVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void Shader::setUniformVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Shader::setUniformVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void Shader::setUniformVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void Shader::setUniformVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void Shader::setUniformVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void Shader::setUniformMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setUniformMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

    
*/




