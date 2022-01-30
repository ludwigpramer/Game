#ifndef _MODEL_HPP
#define _MODEL_HPP
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../constants.hpp"

#include "objloader.hpp"
#include "vboindexing.hpp"
#include "objloader.hpp"
#include "texture.hpp"
#include "shader.hpp"


extern int error;

class Model
{
public:
     //The general info
     // const char* texturepath = "assets/uvmap.DDS";
     // const char* objpath = "assets/suzanne.obj";

     //The location info
     glm::vec3 position;
     glm::mat4 ModelMatrix;

     GLuint* Texture;

     //The mesh data
     std::vector<glm::vec3> vertices;
     std::vector<glm::vec2> uvs;
     std::vector<glm::vec3> normals;

     std::vector<unsigned short> indices;
     std::vector<glm::vec3> indexed_vertices;
     std::vector<glm::vec2> indexed_uvs;
     std::vector<glm::vec3> indexed_normals;

     glm::vec3 ambientLightFactor;
public:
     Model();
     Model(const char* texturepath, const char* objpath);
     Model(const char* texturepath, const char* objpath, glm::vec3 position);
     void setPos(glm::vec3 position);
     void setRot(double alpha, double beta, double gamma);
     void setTexture(const char* texturepath);
     void setTexture(GLuint Texture);
     void setAmbientLightFactor(float factor);
     void setAmbientLightFactor(glm::vec3 factor);
     
     ~Model();
};

#endif