
#include "helpers_gl.hpp"

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
