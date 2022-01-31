#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#ifdef DEBUG
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>



GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

class ShaderProgram
{
     public:
     GLuint program;
     GLuint VertexArrayID;
     GLuint TextureID;

     GLuint MatrixID;
     GLuint ViewMatrixID;
     GLuint ModelMatrixID;

     std::vector<GLuint> LightIDs;
     public:
     ShaderProgram();
     ShaderProgram(const char* vectexfilepath, const char* fragmentfilepath);
     ShaderProgram(GLuint program);
     ~ShaderProgram();
     void use();
     GLuint getUniformLocation(const char* name);
     void bindMatrixID();
     void bindViewMatrixID();
     void bindModelMatrixID();
     void bindTextureID();
     
};

#endif
