/*
This file contains all the helper functions for the current application
*/
#pragma once

#include <fstream>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "structures.hpp"

#include <stb_image.h>

//define all the function

std::string readFile(const char* filePath);
ModelData loadModel(string const &path);


//-------------------------------------------------MODEL LOADER DEFINATION----------------------------------------------------
class ModelLoader{
    public:
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    //vector<myMesh>    meshes;
    string directory;
    bool gammaCorrection;
    ModelData data;
    vector<MeshData> meshdata_array;

    ModelLoader();
    ~ModelLoader();
    ModelData loadModelFile(string const &path);
    ModelData processNode(aiNode *node, const aiScene *scene);
    MeshData processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};
//------------------------------------------------------------------HELPER FUNCTIONS---------------------------------------------
/*
//function to process mesh data
Mesh processVertexData(VertexData vertex_data){
    Mesh mesh;
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

    //positin data
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*) 0);
    glEnableVertexAttribArray(0);

    //uv data
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*) (3*sizeof(float)) );
    glEnableVertexAttribArray(1);
    
    //unbing buffer
    glBindBuffer(GL_ARRAY_BUFFER,0);
    //unbind Vertex Array
    glBindVertexArray(0);

    mesh.VAO = VAO;
    mesh.indices_size = vertex_data.indices.size();

    return mesh;
}
unsigned int loadShader(string vertex_shader_path,string fragment_shader_path){
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




unsigned int loadTexture(const char* filePath){
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


//--------------------------------------------------------------------------------------------------------


    
//model loader class


ModelLoader::ModelLoader(){

}

ModelLoader::~ModelLoader(){
    //cout<<"modelloader is dead"<<endl;
}

ModelData ModelLoader::loadModelFile(string const &path){
// read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        ModelData d;
        return d;
    }
    
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    //std::cout <<directory<<endl;
    
    // process ASSIMP's root node recursively
    ModelData d = processNode(scene->mRootNode, scene);
    for (int i=0;i<textures_loaded.size();i++)
    {
        //cout<<textures_loaded.size()<<endl;
        textures_loaded[i].path = directory+"/"+textures_loaded[i].path;
        d.loaded_textures.push_back({textures_loaded[i].id,textures_loaded[i].path,textures_loaded[i].type});
        //data.loaded_textures[i].path = 
        
    }

    // bind appropriate texture name 
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < d.loaded_textures.size(); i++)
    {
        //glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = d.loaded_textures[i].name;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        d.loaded_textures[i].name=(name + number);
    }
    return d;
}


//write a function to load a model file and return Model data
ModelData ModelLoader::processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //myMesh current_myMesh = processMesh(mesh, scene);
        //meshes.push_back(current_myMesh);

        //get the mesh data from each mesh
        MeshData mesh_data = processMesh(mesh, scene);
        //mesh_data.vertices = current_myMesh.vertices;
        //mesh_data.textures = current_myMesh.textures;
        //mesh_data.indices = current_myMesh.indices;
        meshdata_array.push_back(mesh_data);


    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }


    //extract the modeldata from the model
    //get texture data
    

    //transfer mesh data
    data.mesh_data_array = meshdata_array;
    return data;
}

MeshData ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    vector<TextureData> tex_array;
    for (int i=0;i<textures.size();i++){
        tex_array.push_back({textures[i].id,textures[i].path,textures[i].type});
        
    }
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < tex_array.size(); i++)
    {
        //glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = tex_array[i].name;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        tex_array[i].name=(name + number);
    }
    // return a mesh object created from the extracted mesh data
    //return myMesh(vertices, indices, tex_array);
    MeshData m_data;
    m_data.vertices = vertices;
    m_data.indices = indices;
    m_data.textures = tex_array;

    return m_data;
}

vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = 0;//TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
} 



//function to load models
ModelData loadModel(string const &path){
    ModelLoader loader;
    ModelData data = loader.loadModelFile(path);
    return data;

}
*/