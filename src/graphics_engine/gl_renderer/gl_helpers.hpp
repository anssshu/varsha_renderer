
#pragma once

#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "structures.hpp"

#include <stb_image.h>

#include "../helpers.hpp"//--structures inside the helper//required to load shader files

unsigned int loadShader(string vertex_shader_path,string fragment_shader_path);
unsigned int loadTexture(const char* filePath);
Mesh processVertexData(VertexData vertex_data);