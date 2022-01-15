#include "model.hpp"

Model::Model()
{
     position = glm::vec3(0.0f);
     ModelMatrix = glm::mat4(1.0f);
}

Model::Model(const char* texturepath, const char* objpath)
{
             
     position = glm::vec3(0.0f); 
     ModelMatrix = glm::mat4(1.0f);

     //load the texture
     error = loadDDS(texturepath, &Texture); //loadDDS("imgs/uvmap.DDS");

     if(error != 0)
     {
          fprintf(stderr, "Error: Failed to load Texture: Exit code%d\n", error);
          exit(error);
     }

     //read .obj file    
     error = loadOBJ(objpath, vertices, uvs, normals);
     if(error != 0)
     {
        fprintf(stderr, "Error: Failed to load mesh.\n");
        exit(error);
     }    
     //VBO indexing
     indexVBO(vertices, uvs, normals, indexed_vertices, indexed_uvs, indexed_normals, indices);
}
void Model::setPos(glm::vec3 position)
{
     this->position = position;
     ModelMatrix = glm::translate(ModelMatrix, position);
}

Model::~Model()
{
     	glDeleteTextures(1, &Texture);
}