#ifndef _TEXT_HPP
#define _TEXT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>


#include <GL/glew.h>

#include <glm/glm.hpp>

#include "shader.hpp"
#include "texture.hpp"

void initText(const char * texttexturepath);
void printText(const char * text, int x, int y, int size);
void cleanupText();
#endif