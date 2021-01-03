#include "shader2d_gl.hpp"

GLShader2D::GLShader2D(Shader2DData data){
    shaderProgram = createShaderProgram(data.vs_path,data.fs_path);
}
GLShader2D::GLShader2D(string vertex_shader_path,string fragment_shader_path){
    

    shaderProgram = createShaderProgram(vertex_shader_path,fragment_shader_path);

};
void GLShader2D::loadVertexData(Mesh2D mesh){
    VAO = mesh.VAO;
    indices_size = mesh.indices_size;
}
void GLShader2D::renderContainer(){

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indices_size,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
void GLShader2D::render(){

use();
//bind textures
bindTextures();
//render container
renderContainer();
}
//for rgb falg ==0 ,for rgba flag =1
void GLShader2D::setModelViewProjection(mat4 model,mat4 view ,mat4 projection)
{
    setUniformMat4("model",model);
    setUniformMat4("view",view);
    setUniformMat4("projection",projection);
}
//load a texture file and connect an opengl texture slot to the corresponding name in fragmen shader
void GLShader2D::connectUniformTexturetoTextureSlot(string path,const string name){
    textureCount = loadTexture2D(path.c_str());
    //update texture data base
    //
    //update id with respect to
    textures.push_back({textureCount,path,name});
    use();
    setUniformInt(name,textures.size()-1);
    cout<<"shader.hpp:->loaded_texture-" <<" name:"<<name  <<" id:"<<textureCount<<" slot:"<<textures.size()-1<<" path:"<< path <<endl;
}
//load a single texture file
void GLShader2D::loadTextureData(Texture2DData tex){
    connectUniformTexturetoTextureSlot(tex.path,tex.name);
}
//load multiple texture files
void GLShader2D::loadTextureList(vector<Texture2DData> texture_list){
    for (unsigned int i=0;i<texture_list.size();i++)
    {
        //connectUniformTexturetoTextureSlot(texture_list[i].path,texture_list[i].name);
        loadTextureData(texture_list[i]);

    }

}
// draw the textures
void GLShader2D::bindTextures(){
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

void GLShader2D::use(){
    glUseProgram(shaderProgram);
}

GLShader2D::~GLShader2D(){
    glDeleteProgram(shaderProgram);
    //cout<<"shader is deleted"<<endl;
}

void GLShader2D::setUniformBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void GLShader2D::setUniformVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void GLShader2D::setUniformVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
}
void GLShader2D::setUniformVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GLShader2D::setUniformMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
