#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../constants.hpp"

//Load a .BMP file
GLuint loadBMP(const char * imagepath);

//Load .DDS file
int loadDDS(const char * imagepath, GLuint* Texture);


#endif