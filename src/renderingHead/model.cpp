#include "model.hpp"

Model::Model()
{
     position = glm::vec3(0.0f);
     ModelMatrix = glm::mat4(1.0f);
}

Model::Model(const char* texturepath, const char* objpath)
{
     ambientLightFactor = glm::vec3(0.1, 0.1, 0.1);
     position = glm::vec3(0.0f); 
     ModelMatrix = IDENTITY_MATRIX;

    
     if(error != 0)
     {
          fprintf(stderr, "Error: Failed to load Texture: Exit code%d\n", error);
          exit(error);
     }   
     GLuint T = load(texturepath);
     Texture = &T;
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
     ModelMatrix = glm::translate(IDENTITY_MATRIX, position);
}

void Model::setRot(double alpha, double beta, double gamma)
{
     ModelMatrix = IDENTITY_MATRIX * getRotationMatrix(alpha, beta, gamma);
}
void Model::setTexture(const char* texturepath)
{
     //load the texture
     GLuint T = load(texturepath);
     Texture = &T;
}
void Model::setTexture(GLuint Texture)
{
     this->Texture = &Texture;
}

Model::~Model()
{
     glDeleteTextures(1, Texture);
}

void Model::setAmbientLightFactor(float factor)
{
     ambientLightFactor = glm::vec3(1.0f) * factor;
}
void Model::setAmbientLightFactor(glm::vec3 factor)
{
     ambientLightFactor = factor;
}