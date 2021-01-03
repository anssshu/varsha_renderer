#pragma once
#include "structures2d.hpp"
#include "../../common/file.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//return VAO and indices size from MESH 2d data array of vertices and indices
Mesh2D createMesh2D(Mesh2DData mesh2d_data);

//returns a shader ID
unsigned int createShaderProgram(string vertex_shader_path,string fragment_shader_path);

//returns a texture ID
unsigned int loadTexture2D(const char* filePath);






