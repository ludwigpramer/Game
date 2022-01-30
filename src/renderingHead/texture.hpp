#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../constants.hpp"

typedef enum IMG_TYPE
{
     DDS,
     BMP
}IMG_TYPE;

//Load a Texture(.bmp or .DDS)
GLuint load(const char * imagepath);
GLuint loadBMP(const char* imagepath);
GLuint loadDDS(const char* imagepath);


#endif
