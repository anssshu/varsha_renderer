#include "renderer_gl.hpp"
GLRenderer3D::GLRenderer3D()//:default_shader("shaders/default_shader.vs","shaders/default_shader.fs")
{
    

};

GLRenderer3D::~GLRenderer3D(){
    //delete all the shader pointer of the models
    for (unsigned int i =0;i<model_array.size();i++)
    {
        //delete model_array[i]->shader;
    }
    cout << "renderer got destroyed"<< endl;
};
void GLRenderer3D::addScene(Scene* scene){
    scene_array.push_back(scene);
}
void GLRenderer3D::renderScene()
{
    
    
    //check for current_scene then render the model array
    if (current_scene != nullptr){

        //first update all the model data then render it
        this->update();

        for (unsigned int j=0;j<current_scene->model_array.size();j++)
        {
            //process each model in the model_arrray
        
            Model* model = current_scene->model_array[j];

            //activate shader
            model->shader->use();
            //update uniform data
            //rot+=2.0f;
            //model->setRotY(rot*57);

            //update model view projection matrix
            model->updateModelViewProjectionMatrix(&current_scene->camera);
            //current_scene->camera.updateCamera();

            //render each and every mesh
            unsigned int length = model->mesh_array.size();
            for (unsigned int i =0;i<length;i++)
            {
                

                //bind VAO of the mesh to that of shader
                model->shader->loadVertexData(model->mesh_array[i]);


                //bind textures
                model->shader->bindTextures();

                //render container
                model->shader->renderContainer();
            }
        }
    }
    //render each model inside the scene model_array
    
}
void GLRenderer3D::loadScene(unsigned int ID){
    //if scene is loaed from the file then process it
                //LATER
    if (scene_array.size()>0)
    {
        //point this->scene to the input scene
        this->current_scene = scene_array[ID];

        //process all the model of the scene
        for (unsigned int j=0;j<current_scene->model_array.size();j++)
        {
            //process model data,shader data and load texture to each model
            //create a mesh array
            Model* Pmodel = current_scene->model_array[j];
            Pmodel->mesh_array = processModelData(Pmodel->data);

            //create a shader nad point it to the the model
            Pmodel->shader = new GLShader(Pmodel->shader_data);

            //load texture
            Pmodel->shader->loadTextureList(Pmodel->data.loaded_textures);
            
            //give model an ID;
            Pmodel->ID = model_array.size();
            //loadModel(current_scene->model_array[j]);
        }
    }
    
}

//load model to the curren scene
//process model data,shader data and load texture to a  model
void GLRenderer3D::loadModel(Model* Pmodel){

    //create a mesh array
    Pmodel->mesh_array = processModelData(Pmodel->data);

    //create a shader---current render is OPENGL else chose VULKANShader for vulkan GLESShader
    Pmodel->shader = new GLShader(Pmodel->shader_data);

    //load texture
    Pmodel->shader->loadTextureList(Pmodel->data.loaded_textures);
    
    //give model an ID;
    Pmodel->ID = model_array.size();
    
    //store it;
    model_array.push_back(Pmodel);
    //current_scene->model_array.push_back(Pmodel);
    
}
Mesh GLRenderer3D::processMeshData(MeshData mesh_data){
    Mesh m;
    unsigned int VAO,EBO,VBO,i_size;
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, mesh_data.vertices.size() * sizeof(Vertex), &mesh_data.vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_data.indices.size() * sizeof(unsigned int), &mesh_data.indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
    i_size = mesh_data.indices.size();
    m={VAO,i_size};
    return m;
}
vector<Mesh> GLRenderer3D::processModelData(ModelData model_data)
{   
    //create meshse from the model data and connect it to the model
    vector<Mesh> dummy_mesh_array;
    //get each meshData from model data and store it in the my_meshes
    for (unsigned int i=0;i<model_data.mesh_data_array.size();i++)
    {
        dummy_mesh_array.push_back(processMeshData(model_data.mesh_data_array[i]));
    }
    //my_meshes = dummy_mesh_array;
    return dummy_mesh_array;
}
//load the model to the renderer before rendering it with default shader

//render the mesh with default shader
void GLRenderer3D::renderMesh(Mesh mesh,Shader* shader){

    //code to render a mesh with a default shader
    //activate the default shader

      //bind VAO of the mesh to that of shader
        shader->loadVertexData(mesh);


        //bind textures
        shader->bindTextures();

        //render container
        shader->renderContainer();



}


void GLRenderer3D::renderModel(){
    
    //process each model in the model_arrray
    for (unsigned int j = 0;j<model_array.size();j++)
    {
        
        Model* model = model_array[j];

        //activate shader
        model->shader->use();
        //update uniform data
        rot+=2.0f;
        model->setRotY(rot*57);

        //update model view projection matrix
        model->updateModelViewProjectionMatrix( &current_scene->camera);
        //current_scene->camera.updateCamera();

        //render each and every mesh
        int length = model->mesh_array.size();
        for (int i =0;i<length;i++)
        {
            

            //bind VAO of the mesh to that of shader
            model->shader->loadVertexData(model->mesh_array[i]);


            //bind textures
            model->shader->bindTextures();

            //render container
            model->shader->renderContainer();
        }
    }
    

}


void GLRenderer3D::update()
{
    //update the model and view matrix of the camera
    current_scene->camera.updateCamera();
    //update all the models
    for(unsigned int i=0;i<current_scene->model_array.size();i++)
    {
        current_scene->model_array[i]->update();
    }

    //  
}

void GLRenderer3D::reset()
{

}