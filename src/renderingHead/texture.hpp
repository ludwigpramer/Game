#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../constants.hpp"

//Load a .BMP file
GLuint loadBMP(const char * imagepath);

//Load .DDS file
GLuint loadDDS(const char * imagepath);


#endif
